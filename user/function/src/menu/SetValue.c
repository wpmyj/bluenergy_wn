#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint16_t Data[];
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

	sprintf( preValue, "%f", ((float)newSetValue) / 1000);
	sprintf( value, "%f", ((float)GetData(SV_ADDR)) / 1000);
	
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE); 
	DisplayOneLine12x16_with_params(40, 0, 5, value, FALSE);
	DisplayOneLine12x16_with_params(100, 0, 1, "M", FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, preValue[0], 51);
	DisplayOne12x16(52, 3, preValue[1], FALSE);
	DisplayValueAndSimbol(64, 3, preValue[2], 52);
	DisplayValueAndSimbol(76, 3, preValue[3], 53);
	DisplayValueAndSimbol(88, 3, preValue[4], 54);
	DisplayOneLine12x16_with_params(100, 3, 1, "M", FALSE);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 55) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 56) ? TRUE : FALSE);

}

void UpdateSetValue(uint8_t how)
{
	uint16_t base[4] = {1000, 100, 10, 1};
	uint8_t digit = currentMenu - SET_VAL_BASE;
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

void MoveToFirstValueMenuItem(void)
{
	currentMenu = SET_VAL_BASE;
}

void SetValueKeOptFun(uint8_t key)
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
				newSetValue = GetData(SV_ADDR);;
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
	UpdateData(SV_ADDR, newSetValue);
}

void ChangeValueKeOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateSetValue(ADD);				
				break;
			case DOWN:
				UpdateSetValue(MINUS);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveValueKeOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				MoveToFirstValueMenuItem();
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

	switch(key)
	{
		case UP:
			MoveToLeftMenu();
			break;
		case DOWN:
			MoveToRightMenu();
			break;
		case ENTER:
			MoveToNextMenu();	
			displayModel = DisplayMenu;
			break;
		default:
			break;
	}
}


