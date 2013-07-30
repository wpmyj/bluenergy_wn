#include "Include.h"
#include "Control.h"

uint16_t preOptMod, preOutputMod, changed;

void SaveOptMod(void)
{
	preOptMod = GetData(AM_ADDR);
	preOutputMod = GetData(OCM_ADDR);
}

void SetOptMod(uint16_t optMod, uint16_t outputMod)
{	
	changed = TRUE;
	UpdateData(AM_ADDR, optMod, TRUE);
	UpdateData(OCM_ADDR, outputMod, TRUE);
}

void RestoreOptMod(void)
{
	if(changed == TRUE)
	{
		UpdateData(AM_ADDR, preOptMod, TRUE);
		UpdateData(OCM_ADDR, preOutputMod, TRUE);
		changed = FALSE;
	}
	
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

void OperateValve(uint16_t val)
{
	uint16_t raw;
	
	raw = Convert_MV_To_DAC_Raw(val);

	DacOutput(raw);
}

void ActuatorCheckingTimer(void)
{	
	OperateRelay(GetRelayStatus());
}

void ActuatorTimerInit(void)
{		
	TmrCfg(RELAY_ACTION_TIMER, ActuatorCheckingTimer, (void *)0, 0, 2, 0, FALSE, TRUE);
}

