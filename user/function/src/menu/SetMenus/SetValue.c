#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint8_t Data[];
uint16_t newSetValue;

void DisplayValueAndSimbol(uint8_t x, uint8_t y, char val, uint8_t cMenu)
{
	if(currentMenu == cMenu)
	{
		DisplayOne12x16(x, y - 1, '&', FALSE);
		DisplayOne12x16(x, y + 1, '#', FALSE);
	}	
	DisplayOne12x16(x, y, val, FALSE);
}

void SetValue(void)
{
	char value[5], preValue[5];

	sprintf( preValue, "%4.3f", ((float)newSetValue) / 1000);
	sprintf( value, "%4.3f", ((float)GetData(SV_ADDR)) / 1000);
	
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE); 
	DisplayOneLine12x16_with_params(40, 0, 5, value, FALSE);
	DisplayOneLine12x16_with_params(100, 0, 1, "M", FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, preValue[0], 44);
	DisplayOne12x16(52, 3, preValue[1], FALSE);
	DisplayValueAndSimbol(64, 3, preValue[2], 45);
	DisplayValueAndSimbol(76, 3, preValue[3], 46);
	DisplayValueAndSimbol(88, 3, preValue[4], 47);
	DisplayOneLine12x16_with_params(100, 3, 1, "M", FALSE);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 48) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 49) ? TRUE : FALSE);

}

void UpdateSetValue(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[4] = {1000, 100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newSetValue / base[digit]) % 10;
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
	newSetValue = newSetValue - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void MoveToFirstValueMenuItem(uint8_t menuItem)
{
	currentMenu = menuItem;
}

void SetValueKeyOptFun(uint8_t key)
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
				newSetValue = GetData(SV_ADDR);
				displayModel = SetValue;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveValue(void)
{
	// SAVE to FLASH
	UpdateData(SV_ADDR, newSetValue, TRUE);
}

void ChangeValueKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateSetValue(ADD, SET_VAL_BASE);				
				break;
			case DOWN:
				UpdateSetValue(MINUS, SET_VAL_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveValueKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				MoveToFirstValueMenuItem(SET_VAL_BASE);
				break;
			case DOWN:
				MoveToRightMenu();
				break;
			case ENTER:				
				SaveValue();			
				break;
			default:
				break;
		}
	
}

void ReturnFromSetValueMenuKeyOptFun(uint8_t key)
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
			displayModel = DisplayMenu;
			break;
		default:
			break;
	}
}


