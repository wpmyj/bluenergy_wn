#include "Include.h"
#include "Control.h"

Calibration CalibrationSensor;

uint16_t Convert_ADC_ValueToMeter(uint16_t raw)
{
	long tmp;
	tmp = (long)raw * 3300;
	return (uint16_t)(tmp / 4095);	
}

uint16_t Convert_ADC_ValueToVolage(uint16_t raw)
{
	long tmp;
	tmp = (long)raw * 3300;
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

uint16_t GetCurrentEngineValue(void)
{
	float k, k1, k2, b ,y;

	CalibrationSensor.curRaw = GetVINAdcValue();
	
	k1 = (float)(CalibrationSensor.curRaw - CalibrationSensor.zeroRaw);
	k2 = (float)(CalibrationSensor.refRaw - CalibrationSensor.zeroRaw);
	k = k1 / k2;
	b = (float)CalibrationSensor.mountingHight;
	
	y = k * (CalibrationSensor.refEngine - CalibrationSensor.mountingHight) + b;

	CalibrationSensor.curEngine = (uint16_t)y;

	return CalibrationSensor.curEngine;
}

/* 电流输出为4~20mA */
void CurrentOutput(uint16_t mv)
{
	uint16_t dacOutput, currentOutput;
	dacOutput = Convert_PID_OutputToRaw(mv);
	currentOutput = Convert_DAC_RawToCurrent(dacOutput);
	UpdateData(CO_ADDR, currentOutput, FALSE);
	DacOutput(dacOutput);
}

uint16_t PID_Calc(uint16_t In, uint16_t Ref, uint16_t *Coeff)
{
	uint16_t mv;
	if(In > Ref)
	{
		mv = 0;
	}
	else
	{
		mv = DoFullPID(In, Ref, Coeff) / 1000;	//标定开度(mv)范围为0 ~ 100, Kp范围为1~10 
	}

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
	uint16_t adcVolageIn = Convert_ADC_ValueToVolage(GetVINAdcValue());
	uint16_t currentValue = GetCurrentEngineValue();
	uint16_t setValue = GetData(SV_ADDR);
	uint16_t Coeff[3];
	uint16_t mv;

	Coeff[P] = GetData(P_ADDR);
	Coeff[I] = GetData(I_ADDR);
	Coeff[D] = GetData(D_ADDR);

	UpdateData(VI_ADDR, adcVolageIn, FALSE);	
	
	mv = PID_Calc(currentValue, setValue, Coeff);		
	UpdateData(MV_ADDR, mv, FALSE);
	CurrentOutput(mv);
}

void DO_ThresholdControl(void)
{
	
	uint16_t currentValue = GetCurrentEngineValue();
	uint16_t maxValue, minValue;

	maxValue = GetData(SVH_ADDR);
	minValue = GetData(SVL_ADDR);

	if(currentValue > maxValue)
	{
		UpdateData(RS_ADDR, CLOSE, FALSE);
	} 
	else if(currentValue < minValue)
	{
		UpdateData(RS_ADDR, OPEN, FALSE);
	}

	OperateRelay(GetData(RS_ADDR));
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
		OperateRelay(GetData(RS_ADDR));
	}
}

void AutoControl(void)
{
	if(GetData(OCM_ADDR) == AO_MOD)
	{
		RegulatingValveControl();
	} 
	else if(GetData(OCM_ADDR) == DO_MOD)
	{
		// 自动DO 控制算法
		DO_ThresholdControl();
	}
}

void ControlMode(void)
{
	if(GetData(AM_ADDR) == MANUAL)
	{
		ManualControl();
	} 	
}

void AutoControlHandler(void)
{
	if(GetData(AM_ADDR) == AUTO)
	{
		AutoControl();
	}
}

void AutoControlTimerInit(void)
{
	TmrCfg(AUTO_CONTROL_TIMER, AutoControlHandler, (void *)0, 0, 5, 0, TRUE, TRUE);
}

