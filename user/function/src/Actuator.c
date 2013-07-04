#include "Include.h"

uint16_t preOptMod;

void SaveOptMod(void)
{
	preOptMod = GetData(AM_ADDR);
}

void SetOptMod(uint16_t optMod)
{	
	UpdateData(AM_ADDR, optMod);
}

void RestoreOptMod(void)
{
	UpdateData(AM_ADDR, preOptMod);
}

void OpenRelay(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

void CloseRelay(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

void OperateRelay(uint16_t status)
{
	(status == OPEN) ? OpenRelay() : CloseRelay();
}

