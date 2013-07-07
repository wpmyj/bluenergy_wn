#include "Include.h"
#include "Control.h"

uint16_t Convert_ADC_ValueToMeter(uint16_t raw)
{
	long tmp;
	tmp = (long)raw * 10000;
	return (uint16_t)(tmp / 4095);	
}

uint16_t Convert_PID_OutputToRaw(uint16_t in)
{
	long tmp;
	tmp = (long)in * 4095;
	return (uint16_t)(tmp / 100);
}

uint16_t Convert_DAC_RawToCurrent(uint16_t raw)
{
	long tmp;
	tmp = (long)raw * 20000;
	return (uint16_t)(tmp / 4095);
}

uint16_t Convert_MV_To_DAC_Raw(uint16_t mv)
{
	long tmp;
	tmp = (long)mv * 4095;
	return (uint16_t)(tmp / 100);
}

void CurrentOutput(uint16_t mv)
{
	uint16_t dacOutput, currentOutput;
	dacOutput = Convert_PID_OutputToRaw(mv);
	currentOutput = Convert_DAC_RawToCurrent(dacOutput);
	UpdateData(CO_ADDR, currentOutput);
	DacOutput(dacOutput); 
}

uint16_t PID_Calc(uint16_t In, uint16_t Ref, uint16_t *Coeff)
{
	uint16_t mv;
	
	mv = DoFullPID(In, Ref, Coeff);

	if(mv > 100)
	{
		mv = 100;
	} 
	else if(mv < 0)
	{
		mv = 0;
	}
	
	return mv;
}


void RegulatingValveControl(void)
{
	uint16_t adcVolageIn = GetVINAdcValue();
	uint16_t currentValue = Convert_ADC_ValueToMeter(adcVolageIn & 0xfff);
	uint16_t setValue = GetData(SV_ADDR);
	uint16_t Coeff[3];
	uint16_t mv;

	Coeff[P] = GetData(P_ADDR);
	Coeff[I] = GetData(I_ADDR);
	Coeff[D] = GetData(D_ADDR);

	UpdateData(VI_ADDR, adcVolageIn);	
	UpdateData(PV_ADDR, currentValue);
	
	mv = PID_Calc(currentValue, setValue, Coeff);		
	UpdateData(MV_ADDR, mv);
	CurrentOutput(mv);	
}

void ManualControl(void)
{
	if(GetData(OCM_ADDR) == AO_MOD)
	{
		//手动AO控制算法
		OperateValve(GetData(MV_ADDR));
	} 
	else if(GetData(AM_ADDR) == DO_MOD)
	{
		OperateRelay(DO);
	}
}

void AutoControl(void)
{
	if(GetData(OCM_ADDR) == AO_MOD)
	{
		RegulatingValveControl();
	} 
	else if(GetData(AM_ADDR) == DO_MOD)
	{
		// 自动DO 控制算法
	}
}

void ControlMode(void)
{
	if(GetData(AM_ADDR) == MANUAL)
	{
		ManualControl();
	} 
	else if(GetData(AM_ADDR) == AUTO)
	{
		AutoControl();
	}
}

