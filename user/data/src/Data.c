#include "Include.h"

uint16_t Data[];
uint16_t DO;

uint16_t GetData(uint16_t type)
{
	return Data[type];
}

void UpdateData(uint8_t type, uint16_t val)
{
	Data[type] = val;
}

uint16_t GetRelayStatus(void)
{
	return DO;
}

void SetRelay(int16_t status)
{
	DO = status;
}


