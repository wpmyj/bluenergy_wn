#include "Include.h"

extern uint8_t needRefresh;

uint8_t Data[];

extern __IO uint32_t DataStartAddr = FLASH_DATA_ADDR;

uint16_t GetData(uint16_t type)
{
	uint8_t typeAddr = type * 2;
	
	uint16_t returnVal;
	returnVal = Data[typeAddr];
	returnVal = (returnVal << 8) + Data[typeAddr + 1];
	
	return returnVal;
}

void LoadDataFromFlash(void)
{	
	uint8_t i = 0;
	uint16_t val;

	for(i = OCM_ADDR; i < 64; i++)
	{	
		val = ReadFlash_by_16Bit(DataStartAddr + i * 2);
		Data[i * 2] = (uint8_t)(val >> 8);
		Data[i * 2 + 1] = (uint8_t)(val & 0x00ff);
	}
	
}

void SaveDataToFlash(void)
{
	uint8_t i = 0;
	uint16_t val;
	
	EraseFlash(DataStartAddr, DataStartAddr + 128);
	
	for(i = OCM_ADDR; i < 64; i++)
	{	
		val = (uint16_t)(Data[i * 2]) << 8;
		val += Data[i * 2 + 1];
		if(TRUE == WriteFlash_by_16Bit(DataStartAddr + (uint32_t)(i * 2), val))
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_12);
		} else {
			GPIO_ResetBits(GPIOA, GPIO_Pin_12);
		}
	}
}

void UpdateData(uint8_t type, uint16_t val, bool writeToFlash)
{
	uint8_t typeAddr = type * 2;
		
	Data[typeAddr] = (uint8_t)((val & 0xff00) >> 8);
	Data[typeAddr + 1] = (uint8_t)(val & 0xff);

	if(writeToFlash == TRUE)
	{
		SaveDataToFlash();
	}
}

uint16_t GetRelayStatus(void)
{
	return GetData(RS_ADDR);
}

void SetRelay(int16_t status)
{
	UpdateData(RS_ADDR, status, FALSE);
}

bool NeedToWriteDefaultValueToFlash(void)
{
	uint16_t flag, returnVal = FALSE;
	
	flag = ReadFlash_by_16Bit(FLASH_OPT_FLAG_ADDR);

	if(0x55AA != flag)
	{
		WriteFlash_by_16Bit(FLASH_OPT_FLAG_ADDR, 0x55AA);
		returnVal = TRUE;
	}

	return returnVal;
}

void ConvertStringToWordArray(char *src, uint16_t *dst)
{
	uint8_t i = 0;

	for(i = 0; i < (strlen(src) / 2) + 1; i++)
	{
		dst[i] = ((uint16_t)src[i * 2] << 8) + (uint16_t)src[i * 2 + 1];
	}
}

void ConvertAsciiToWordArray(char *src, uint16_t *dst)
{
	uint8_t i = 0;

	for(i = 0; i < (strlen(src)) + 1; i++)
	{
		dst[i] = (uint16_t)src[i];
	}
}

void WriteDefaultValueToFlash(void)
{
	uint8_t i = 0;
	uint16_t vender[9], product[9];
	uint16_t rangeData[] = {
		0,	//�������ģʽ��0-AO��1-DO��						--0--
		0,		//�Զ�/�ֶ�ģʽ��0-�Զ���1-�ֶ���			--1--
		8000,	//�������ޣ�8m��								--2--
		0,	//�������ޣ�0m��									--3--
		7000,	//�澯����7000									--4--
		1000,	//�澯����1000									--5--
		7800,//�澯������7800									--6--
		500,	//�澯������500									--7--
		5000,	//�趨Һλ5000									--8--
		0,	//��ǰҺλ											--9--
	};
	
	uint16_t paramsData[] = {
		0,	//AO�����������ƣ�0-����1-����					--20--
  		1,	//����ϵ�����˴���ʾ�����˲�ʱ�䳣����0��32s��	--21--
 		100,	//PID���ֵ�����ſ��ȣ�0��100%��					--22--
		10,	//��������:1~10												--23--
		0,		//����ʱ��												--24--
		0,		//΢��ʱ��												--25--
		0,	//�����������ź����										--26--
		0,	//��������ѹ�ź�����										--27--
		24,	//24V�������� mV												--28--
		6000,	//�趨Һλ���ޣ�DOʹ�ã�							--29--
		4000,	//�趨Һλ���ޣ�DOʹ�ã�							--30--
		0,	//�̵���״̬��0-�أ�1-����								--31--
		1,	//�豸��ַ													--32--
		0,	//Һλ��ʼ�߶ȣ���������װ�߶ȣ�					--33--
		310,	//���ԭʼֵ											--34--
		4033,	//�ο���ԭʼֵ											--35--
		8000,	//�ο��㹤��ֵmm										--36--
		1,		//�Զ����� ��������									--37--													
		3000,	//PID�ֵ�Һλ�߶Ȳ�									--38--
		0,		//Error Code													--39--
		10		//Modbus timeout time 											--40--
	};

	//Init default range data
	for(i = 0; i < 20; i++)
	{
		UpdateData(OCM_ADDR + i, rangeData[i], FALSE);
	}

	//init default params data
	for(i = 0; i < 21; i++)
	{
		UpdateData(AOFR_ADDR + i, paramsData[i], FALSE);
	}

	ConvertStringToWordArray("����ά��", vender);
	for(i = 0; i < 9; i++)
	{
		UpdateData(VENDOR0_ADDR + i, vender[i], FALSE);
	}

	ConvertAsciiToWordArray("ABC-0123", product);
	for(i = 0; i < 9; i++)
	{
		UpdateData(PRODUCT0_ADDR + i, product[i], FALSE);
	}

	UpdateData(R_YEAR_ADDR, 0x2013, FALSE);
	UpdateData(R_DATE_ADDR, 0x0616, FALSE);
	UpdateData(Q_YEAR_ADDR, 0x2013, FALSE);
	UpdateData(Q_DATE_ADDR, 0x0617, FALSE);
	
	SaveDataToFlash();
}

void SystemParamsInit(void)
{
	//EraseFlash(FLASH_OPT_FLAG_ADDR, FLASH_OPT_FLAG_ADDR + 128);
	if(NeedToWriteDefaultValueToFlash() == TRUE)
	{		
		WriteDefaultValueToFlash();
	}
	LoadDataFromFlash();
}

