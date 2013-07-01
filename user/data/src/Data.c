#include "Include.h"

uint16_t Data[];

uint16_t GetData(uint16_t type)
{
	return Data[type] = rand();
}

void UpdateData(uint8_t type, uint8_t val)
{
	Data[type] = val;
}

