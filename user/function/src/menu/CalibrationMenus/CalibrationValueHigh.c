#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "CalibrationStartValue.h"
#include "CalibrationValueHigh.h"
#include "SetValue.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newValueHigh;

void DisplayCalibrationValueHigh(void)
{
	
	char value[5], preValue[5];
	
		sprintf( preValue, "%4.3f", ((float)newValueHigh) / 1000);
		sprintf( value, "%4.3f", ((float)CalibrationSensor.refEngine) / 1000);
		
		DisplayOneLine16x16_with_params(4, 0, 7, "请输入当前液位", FALSE); 		
		
		DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
		DisplayValueAndSimbol(40, 3, preValue[0], 159);
		DisplayOne12x16(52, 3, preValue[1], FALSE);
		DisplayValueAndSimbol(64, 3, preValue[2], 160);
		DisplayValueAndSimbol(76, 3, preValue[3], 161);
		DisplayValueAndSimbol(88, 3, preValue[4], 162);
		DisplayOneLine12x16_with_params(100, 3, 1, "M", FALSE);
	
		DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 163) ? TRUE : FALSE);
		DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 164) ? TRUE : FALSE);	

}

void DisplayCalibrationValueHighKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				MoveToLeftMenu();
				break;
			case DOWN:
				MoveToRightMenu();
				break;
			case ENTER:
				newValueHigh = CalibrationSensor.refEngine;
				displayModel = DisplayCalibrationValueHigh;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void UpdateValueHigh(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[4] = {1000, 100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newValueHigh / base[digit]) % 10;
	uint16_t singleValue = digitValue;

	if(how == ADD)
	{
		singleValue += 1;
		
	} 
	else if(how == MINUS)
	{
		singleValue += 9;
	}
	singleValue %= 10;
	newValueHigh = newValueHigh - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void ChangeValueHighkeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateValueHigh(ADD, VALUE_HIGH_BASE);				
				break;
			case DOWN:
				UpdateValueHigh(MINUS, VALUE_HIGH_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveValueHigh(void)
{
	uint16_t currentADC_Value = GetVINAdcValue();
	
	UpdateData(RE_ADDR, newValueHigh, TRUE);
	CalibrationSensor.refEngine = newValueHigh;

	UpdateData(RR_ADDR, currentADC_Value, TRUE);
	CalibrationSensor.refRaw= currentADC_Value;
}

void SaveValueHighKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				MoveToLeftMenu();
				break;
			case DOWN:
				MoveToRightMenu();
				break;
			case ENTER:				
				SaveValueHigh();				
				break;
			default:
				break;
		}
	
}

void ReturnFromCalibrateMenuKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	StopScreenRefreshTimer();
	switch(key)
	{
		case UP:
			MoveToLeftMenu();
			break;
		case DOWN:
			MoveToRightMenu();
			break;
		case ENTER:
			RestoreOptMod();
			MoveToNextMenu();
			MenuTimeoutTimerInit();
			displayModel = DisplayMenu;
			break;
		default:
			break;
	}
}

