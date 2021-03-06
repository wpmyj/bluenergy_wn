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
		0,	//输出控制模式（0-AO，1-DO）						--0--
		0,		//自动/手动模式（0-自动，1-手动）			--1--
		8000,	//量程上限（8m）								--2--
		0,	//量程上限（0m）									--3--
		7000,	//告警上限7000									--4--
		1000,	//告警上限1000									--5--
		7800,//告警上上限7800									--6--
		500,	//告警下下限500									--7--
		5000,	//设定液位5000									--8--
		0,	//当前液位											--9--
	};
	
	uint16_t paramsData[] = {
		0,	//AO输出正反向控制（0-正向，1-反向）					--20--
  		1,	//阻尼系数，此处表示数字滤波时间常数（0～32s）	--21--
 		100,	//PID输出值（阀门开度：0～100%）					--22--
		10,	//比例增益:1~10												--23--
		0,		//积分时间												--24--
		0,		//微分时间												--25--
		0,	//控制器电流信号输出										--26--
		0,	//传感器电压信号输入										--27--
		24,	//24V供电输入 mV												--28--
		6000,	//设定液位上限（DO使用）							--29--
		4000,	//设定液位下限（DO使用）							--30--
		0,	//继电器状态（0-关，1-开）								--31--
		1,	//设备地址													--32--
		0,	//液位初始高度（传感器安装高度）					--33--
		310,	//零点原始值											--34--
		4033,	//参考点原始值											--35--
		8000,	//参考点工程值mm										--36--
		1,		//自动控制 调度周期									--37--													
		3000,	//PID粗调液位高度差									--38--
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

	ConvertStringToWordArray("西安维纳", vender);
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

