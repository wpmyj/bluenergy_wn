#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "SetRangeH.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newRangeHigh;

void SetRangeHigh(void)
{
	char value[5], preValue[5];

	sprintf( preValue, "%4.3f", ((float)newRangeHigh) / 1000);
	sprintf( value, "%4.3f", ((float)GetData(RH_ADDR)) / 1000);
	
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE); 
	DisplayOneLine12x16_with_params(40, 0, 5, value, FALSE);
	DisplayOneLine12x16_with_params(100, 0, 1, "m", FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, preValue[0], 74);
	DisplayOne12x16(52, 3, preValue[1], FALSE);
	DisplayValueAndSimbol(64, 3, preValue[2], 75);
	DisplayValueAndSimbol(76, 3, preValue[3], 76);
	DisplayValueAndSimbol(88, 3, preValue[4], 77);
	DisplayOneLine12x16_with_params(100, 3, 1, "m", FALSE);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 78) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 79) ? TRUE : FALSE);

}

void UpdateRangeHigh(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[4] = {1000, 100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newRangeHigh / base[digit]) % 10;
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
	newRangeHigh = newRangeHigh - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void SetRangeHighKeyOptFun(uint8_t key)
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
				newRangeHigh = GetData(RH_ADDR);
				displayModel = SetRangeHigh;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveRangeHigh(void)
{
	// SAVE to FLASH
	UpdateData(RH_ADDR, newRangeHigh, TRUE);
}

void ChangeRangeHighkeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateRangeHigh(ADD, SET_RANGE_HIGH_BASE);				
				break;
			case DOWN:
				UpdateRangeHigh(MINUS, SET_RANGE_HIGH_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveRangeHighKeyOptFun(uint8_t key)
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
				SaveRangeHigh();			
				break;
			default:
				break;
		}
	
}

