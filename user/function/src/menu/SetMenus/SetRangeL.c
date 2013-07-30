#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "SetRangeL.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newRangeLow;

void SetRangeLow(void)
{
	char value[5], preValue[5];

	sprintf( preValue, "%4.3f", ((float)newRangeLow) / 1000);
	sprintf( value, "%4.3f", ((float)GetData(RL_ADDR)) / 1000);
	
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE); 
	DisplayOneLine12x16_with_params(40, 0, 5, value, FALSE);
	DisplayOneLine12x16_with_params(100, 0, 1, "M", FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, preValue[0], 80);
	DisplayOne12x16(52, 3, preValue[1], FALSE);
	DisplayValueAndSimbol(64, 3, preValue[2], 81);
	DisplayValueAndSimbol(76, 3, preValue[3], 82);
	DisplayValueAndSimbol(88, 3, preValue[4], 83);
	DisplayOneLine12x16_with_params(100, 3, 1, "M", FALSE);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 84) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 85) ? TRUE : FALSE);

}

void UpdateRangeLow(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[4] = {1000, 100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newRangeLow / base[digit]) % 10;
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
	newRangeLow = newRangeLow - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void SetRangeLowKeyOptFun(uint8_t key)
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
				newRangeLow = GetData(RL_ADDR);
				displayModel = SetRangeLow;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveRangeLow(void)
{
	// SAVE to FLASH
	UpdateData(RL_ADDR, newRangeLow, TRUE);
}

void ChangeRangeLowkeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateRangeLow(ADD, SET_RANGE_LOW_BASE);				
				break;
			case DOWN:
				UpdateRangeLow(MINUS, SET_RANGE_LOW_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveRangeLowKeyOptFun(uint8_t key)
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
				SaveRangeLow();			
				break;
			default:
				break;
		}
	
}

