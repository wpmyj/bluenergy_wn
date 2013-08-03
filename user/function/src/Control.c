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

uint16_t Convert_MV_To_DAC_Raw(uint16_t in)
{
	long tmp;
	//回采adc参考电压, 通过参考电压修正当前adc值
	if(in >= 0 && in <= 100)
	{
		if(GetData(AOFR_ADDR) == 1)
		{
			in = 100 - in;	
		}
		tmp = (long)in * 2979;		
		return (uint16_t)(tmp / 100) + 750;
	} else 
	{
		return (GetData(AOFR_ADDR) == 0) ? 0 : 3724;
	}
	
}

uint16_t Convert_DAC_RawToCurrent(uint16_t raw)
{
	long tmp;
	tmp = (long)raw * 20000;
	return (uint16_t)(tmp / 4095);
}

uint16_t GetCurrentEngineValue(uint16_t curRaw)
{
	float k, k1, k2, b ,y;
	CalibrationSensor.curRaw = curRaw;

	if((CalibrationSensor.curRaw >= CalibrationSensor.zeroRaw)
		&& (CalibrationSensor.refRaw > CalibrationSensor.zeroRaw)
		&& (CalibrationSensor.refEngine > CalibrationSensor.mountingHight))
	{				
		k1 = (float)(CalibrationSensor.curRaw - CalibrationSensor.zeroRaw);
		k2 = (float)(CalibrationSensor.refRaw - CalibrationSensor.zeroRaw);
		k = k1 / k2;
		b = (float)CalibrationSensor.mountingHight;
		
		y = k * (CalibrationSensor.refEngine - CalibrationSensor.mountingHight) + b;

		CalibrationSensor.curEngine = (uint16_t)y;
		return CalibrationSensor.curEngine;
	}
	else
	{
		return GetData(RH_ADDR);
	}
	
}

/* 电流输出为4~20mA */
void CurrentOutput(uint16_t mv)
{
	uint16_t dacOutput, currentOutput;
	dacOutput = Convert_MV_To_DAC_Raw(mv);
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
	else if(Ref - In > 3000)
	{
		mv = 100;
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
	uint16_t currentValue = GetCurrentEngineValue(GetVINAdcValue());
	uint16_t setValue = GetData(SV_ADDR);
	uint16_t Coeff[3];
	uint16_t mv;
	/* PID 数据有效性判断与出错处理 */
	Coeff[P] = GetData(P_ADDR);
	Coeff[I] = GetData(I_ADDR);
	Coeff[D] = GetData(D_ADDR);

	UpdateData(VI_ADDR, adcVolageIn, FALSE);	
	
	mv = PID_Calc(currentValue, setValue, Coeff);		
	UpdateData(MV_ADDR, mv, FALSE);
	CurrentOutput(mv);//闭环检测，修正
}

void DO_ThresholdControl(void)
{
	
	uint16_t currentValue = GetCurrentEngineValue(GetVINAdcValue());
	uint16_t maxValue, minValue;

	maxValue = GetData(SVH_ADDR);
	minValue = GetData(SVL_ADDR);
	/*[MODIFY] 加越界保护, 数据合法性检查max < alarm high
	  min > alarm low
	*/
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

