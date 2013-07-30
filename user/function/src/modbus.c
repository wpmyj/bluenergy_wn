#define CRC_TBL

#include "Include.h"

void parseModbusPackage(void);

extern COM com2;
extern uint8_t Data[];

void ModbusRecTimeoutTimerHanler(void)
{	
	com2.RecLen = com2.RecCnt;
	com2.RecCnt = 0;
	com2.RecOk = 1; 
	parseModbusPackage();
}

void ModbusRecTimeoutTimerInit(void)
{
	TmrCfg(USART_REC_TIMEOUT_TIMER, ModbusRecTimeoutTimerHanler, (void *)0, 0, 0, 1, FALSE, FALSE);
}

//从串口获取数据
bool RdCom(COM *pCOM,uint8_t *RBuf,uint8_t* NumOfDataRecv)
{
	if((pCOM->RecOk == 1) && (pCOM->TrCnt == 0))
	{
		pCOM->RecOk = 0;
		*NumOfDataRecv=0;
		*NumOfDataRecv=pCOM->RecLen;
		memcpy(RBuf,&com2.recBuf[0],pCOM->RecLen);
		return TRUE;
	}
	else return FALSE;
}

//写数据到串口
void WrCom(COM  *pCOM,uint8_t *WBuf,uint8_t NumOfDataTrans)
{	
	RS485_RW_Select(RS485_WRITE);
	while(pCOM->TrCnt != 0);							//等待上一次发送完
	memcpy(pCOM->trBuf,WBuf,NumOfDataTrans);
	pCOM->TrLen = NumOfDataTrans;
	pCOM->TrCnt = 0;
	/* Open USART2 to send acknowledged package */
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	
	
}

//计算CRC校验和
uint16_t CRC16(uint8_t *pDataIn, uint16_t nLenIn)
{
	uint8_t nTemp;
	uint16_t wCRCWord = 0xFFFF;

   while (nLenIn--)
   {
	  nTemp = *pDataIn++ ^ wCRCWord;
	  wCRCWord >>= 8;
	  wCRCWord ^= wCRCTable[nTemp];
   }

   return wCRCWord;
}

//接收数据报校验
bool RecPakChk(uint8_t  *buf,uint8_t LenOfRecPak)
{
	uint16_t ChkSum;
	ChkSum = (uint16_t)buf[LenOfRecPak-1] * 256 + (uint16_t)buf[LenOfRecPak - 2];
	if(CRC16(buf,LenOfRecPak-2) == ChkSum)return TRUE;
	else return FALSE;
}

//发送数据报校验
void TrPakChk(uint8_t  *buf,uint8_t LenOfTrPak)
{
	buf[LenOfTrPak-1] = (CRC16(buf,(LenOfTrPak-2))) >> 8;
	buf[LenOfTrPak-2] = CRC16(buf,(LenOfTrPak-2));
}

bool getModbusPackage(uint8_t *pFncCode,			                    /*返回功能码*/
						   uint16_t *pDataStartAddr,	                            /*返回数据地址*/
						   uint16_t *pDataNum,
						   uint8_t *pData)
{
	uint8_t rbuf[128];
	uint8_t rlen;
	if(RdCom(&com2, rbuf, &rlen) == TRUE)				                            /*从串口获取数据*/
	{
		if(rbuf[0] == (uint8_t)GetData(DA_ADDR))							                    	/*校验设备地址*/
		{
			if(RecPakChk(rbuf,rlen) == TRUE)										/*CRC校验*/
			{
				uint16_t i = (uint16_t)rbuf[2] * 256 + rbuf[3];
				uint16_t j = (uint16_t)rbuf[4] * 256 + rbuf[5];
				*pFncCode = rbuf[1];									         /*返回功能码*/
				*pDataStartAddr = i;
				if(*pFncCode == 0x05)
				{
					memcpy(pData, &rbuf[4], 2);		
				}
				else
				{
					*pDataNum = j;
					memcpy(pData, &rbuf[7], j * 2);
				}
				//Modbus异常返回数据报处理
				//...
				//...
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

void parseModbusPackage(void)
{
	uint8_t fncCode;			                    /*返回功能码*/
	uint16_t dataStartAddr;	                            /*返回数据地址*/
	uint16_t dataNum;
	uint8_t	trBuf[64];
	uint8_t dataBuf[64];
	
	if(getModbusPackage(&fncCode, &dataStartAddr, &dataNum, dataBuf) == TRUE)
	{
		switch(fncCode)
		{
			case RD_HOLD_REG:
				trBuf[0] = (uint8_t)GetData(DA_ADDR);
				trBuf[1] = fncCode;
				trBuf[2] = dataNum * 2;	//bytes				
				memcpy(&trBuf[3], &Data[dataStartAddr * 2], dataNum * 2);				
				TrPakChk(trBuf, 5 + dataNum * 2);

				WrCom(&com2, trBuf, 5 + dataNum * 2);

				break;
			case WR_MULT_HOLD_REG:
				//接收数据
				memcpy(&Data[dataStartAddr * 2], &dataBuf[0], dataNum * 2);
				SaveDataToFlash();
				//响应写多个寄存器
				trBuf[0] = (uint8_t)GetData(DA_ADDR);
				trBuf[1] = fncCode;
				trBuf[2] = 0;	
				trBuf[3] = dataStartAddr;	//bytes										
				trBuf[4] = 0;	
				trBuf[5] = dataNum;	//bytes						
				TrPakChk(trBuf, 8);

				WrCom(&com2, trBuf, 8);
				break;
			case WR_SINGAL_COIL:
				if((GetData(AM_ADDR) == MANUAL) && (GetData(AM_ADDR) == DO_MOD))
				{
					if((dataBuf[0] == 0xff) && (dataBuf[1] == 0x00))
					{
						UpdateData(RS_ADDR, OPEN, FALSE);
					}
					else if((dataBuf[0] == 0x00) && (dataBuf[1] == 0x00))
					{
						UpdateData(RS_ADDR, CLOSE, FALSE);
					}					
					trBuf[0] = (uint8_t)GetData(DA_ADDR);
					trBuf[1] = fncCode;
					trBuf[2] = 0;	
					trBuf[3] = dataStartAddr;	//bytes							
					trBuf[4] = dataBuf[0];	
					trBuf[5] = dataBuf[1];
					TrPakChk(trBuf, 8);
					
					WrCom(&com2, trBuf, 8);
				}				
				break;
			default:
				break;
		}
	}
}

