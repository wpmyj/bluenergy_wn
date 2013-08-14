#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "CalibrationStartValue.h"
#include "CalibrationValueLow.h"
#include "CalibrationValueHigh.h"
#include "SetValue.h"
#define CL_ADDR 128
extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newValueLow;

void DisplayCalibrationValueLow(void)
{
	
	char value[5], preValue[5];
	
		sprintf( preValue, "%4.3f", ((float)newValueLow) / 1000);
		sprintf( value, "%4.3f", ((float)GetData(CL_ADDR)) / 1000);
		
		DisplayOneLine16x16_with_params(4, 0, 4, "初始液位", FALSE); 
		DisplayOneLine12x16_with_params(70, 0, 5, value, FALSE);
		
		DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
		DisplayValueAndSimbol(40, 3, preValue[0], 153);
		DisplayOne12x16(52, 3, preValue[1], FALSE);
		DisplayValueAndSimbol(64, 3, preValue[2], 154);
		DisplayValueAndSimbol(76, 3, preValue[3], 155);
		DisplayValueAndSimbol(88, 3, preValue[4], 156);
		DisplayOneLine12x16_with_params(100, 3, 1, "m", FALSE);
	
		DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 157) ? TRUE : FALSE);
		DisplayOneLine16x16_with_params(83, 6, 3, "下一步", (currentMenu == 158) ? TRUE : FALSE);	

}

void DisplayCalibrationValueLowKeyOptFun(uint8_t key)
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
				newValueLow = GetData(CL_ADDR);
				displayModel = DisplayCalibrationValueLow;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void UpdateValueLow(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[4] = {1000, 100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newValueLow / base[digit]) % 10;
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
	newValueLow = newValueLow - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void ChangeValueLowkeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateValueLow(ADD, VALUE_LOW_BASE);				
				break;
			case DOWN:
				UpdateValueLow(MINUS, VALUE_LOW_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveValueLow(void)
{
	// SAVE to FLASH
	UpdateData(CL_ADDR, newValueLow, TRUE);
}

void SaveValueLowKeyOptFun(uint8_t key)
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
				SaveValueLow();				
				break;
			default:
				break;
		}
	
}

