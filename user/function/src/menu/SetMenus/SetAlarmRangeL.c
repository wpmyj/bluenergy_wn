#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "SetAlarmRangeL.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newAlarmRangeLow;

void SetAlarmRangeLow(void)
{
	char value[5], preValue[5];

	sprintf( preValue, "%4.3f", ((float)newAlarmRangeLow) / 1000);
	sprintf( value, "%4.3f", ((float)GetData(AL_ADDR)) / 1000);
	
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE); 
	DisplayOneLine12x16_with_params(40, 0, 5, value, FALSE);
	DisplayOneLine12x16_with_params(100, 0, 1, "m", FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, preValue[0], 98);
	DisplayOne12x16(52, 3, preValue[1], FALSE);
	DisplayValueAndSimbol(64, 3, preValue[2], 99);
	DisplayValueAndSimbol(76, 3, preValue[3], 100);
	DisplayValueAndSimbol(88, 3, preValue[4], 101);
	DisplayOneLine12x16_with_params(100, 3, 1, "m", FALSE);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 102) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 103) ? TRUE : FALSE);

}

void UpdateAlarmRangeLow(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[4] = {1000, 100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newAlarmRangeLow / base[digit]) % 10;
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
	newAlarmRangeLow = newAlarmRangeLow - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void SetAlarmRangeLowKeyOptFun(uint8_t key)
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
				newAlarmRangeLow = GetData(AL_ADDR);
				displayModel = SetAlarmRangeLow;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveAlarmRangeLow(void)
{
	// SAVE to FLASH
	UpdateData(AL_ADDR, newAlarmRangeLow, TRUE);
}

void ChangeAlarmRangeLowkeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateAlarmRangeLow(ADD, SET_ALARM_RANGE_LOW_BASE);				
				break;
			case DOWN:
				UpdateAlarmRangeLow(MINUS, SET_ALARM_RANGE_LOW_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveAlarmRangeLowKeyOptFun(uint8_t key)
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
				SaveAlarmRangeLow();			
				break;
			default:
				break;
		}
	
}

