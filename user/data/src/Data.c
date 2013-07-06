#include "Include.h"

extern uint8_t needRefresh;

uint8_t Data[];
uint16_t DO;

uint16_t GetData(uint16_t type)
{
	uint16_t returnVal;
	returnVal = Data[type];
	returnVal = (returnVal << 8) + Data[type + 1];
	
	return returnVal;
}

void UpdateData(uint8_t type, uint16_t val)
{
	Data[type] = (uint8_t)((val & 0xff00) >> 8);
	Data[type + 1] = (uint8_t)(val & 0xff);
}

uint16_t GetRelayStatus(void)
{
	return DO;
}

void SetRelay(int16_t status)
{
	DO = status;
}

void SystemParamsInit(void)
{
	UpdateData(SV_ADDR, 5000);
	UpdateData(P_ADDR, 4);
	UpdateData(I_ADDR, 0);
	UpdateData(D_ADDR, 0);
	UpdateData(DAMP_ADDR, 1);
}

