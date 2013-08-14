#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "CalibrationStartValue.h"
#include "CalibrationZero.h"
#include "SetValue.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newStartValue;

void DisplayCalibrationStartValue(void)
{
	
	char value[5], preValue[5];
	
		sprintf( preValue, "%4.3f", ((float)newStartValue) / 1000);
		sprintf( value, "%4.3f", ((float)GetData(MH_ADDR)) / 1000);
		
		DisplayOneLine16x16_with_params(4, 0, 4, "安装高度", FALSE); 
		DisplayOneLine12x16_with_params(70, 0, 5, value, FALSE);
		
		DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
		DisplayValueAndSimbol(40, 3, preValue[0], 147);
		DisplayOne12x16(52, 3, preValue[1], FALSE);
		DisplayValueAndSimbol(64, 3, preValue[2], 148);
		DisplayValueAndSimbol(76, 3, preValue[3], 149);
		DisplayValueAndSimbol(88, 3, preValue[4], 150);
		DisplayOneLine12x16_with_params(100, 3, 1, "m", FALSE);
	
		DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 151) ? TRUE : FALSE);
		DisplayOneLine16x16_with_params(83, 6, 3, "下一步", (currentMenu == 152) ? TRUE : FALSE);	

}

void DisplayCalibrationStartValueKeyOptFun(uint8_t key)
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
				MenuTimeoutTimerStop();
				newStartValue = GetData(MH_ADDR);
				displayModel = DisplayCalibrationStartValue;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void UpdateStartValue(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[4] = {1000, 100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newStartValue / base[digit]) % 10;
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
	newStartValue = newStartValue - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void ChangeStartValuekeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateStartValue(ADD, START_VALUE_BASE);				
				break;
			case DOWN:
				UpdateStartValue(MINUS, START_VALUE_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveStartValue(void)
{
	UpdateData(MH_ADDR, newStartValue, TRUE);
}

void SaveStartValueKeyOptFun(uint8_t key)
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
				SaveStartValue();				
				break;
			default:
				break;
		}
	
}

void MoveToSetValueLowKeyOptFun(uint8_t key)
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
				displayModel = DisplayCalibrationZero;
				MoveToNextMenu();
				break;
			default:
				break;
		}
	
}

