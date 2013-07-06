#include "Include.h"

uint16_t preOptMod, preOutputMod;

void SaveOptMod(void)
{
	preOptMod = GetData(AM_ADDR);
	preOutputMod = GetData(OCM_ADDR);
}

void SetOptMod(uint16_t optMod, uint16_t outputMod)
{	
	UpdateData(AM_ADDR, optMod);
	UpdateData(OCM_ADDR, outputMod);
}

void RestoreOptMod(void)
{
	UpdateData(AM_ADDR, preOptMod);
	UpdateData(OCM_ADDR, preOutputMod);
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

void ActuatorCheckingTimer(void)
{	
	OperateRelay(GetRelayStatus());
}

void ActuatorTimerInit(void)
{		
	TmrCfg(RELAY_ACTION_TIMER, ActuatorCheckingTimer, (void *)0, 0, 2, 0, FALSE, TRUE);
}

