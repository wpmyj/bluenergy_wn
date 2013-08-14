#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "SetDampValue.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newDampValue;

void SetDampValue(void)
{
	
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE); 
	DisplayOne12x16(40, 0, ((GetData(DAMP_ADDR) / 10) % 10) + 48, FALSE);
	DisplayOne12x16(64, 0, (GetData(DAMP_ADDR) % 10) + 48, FALSE);
	DisplayOneLine12x16_with_params(100, 0, 1, "s", FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, ((newDampValue / 10) % 10) + 48, 123);
	DisplayValueAndSimbol(64, 3, (newDampValue % 10) + 48, 124);
	DisplayOneLine12x16_with_params(100, 3, 1, "s", FALSE);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 125) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 126) ? TRUE : FALSE);

}

void UpdateDampValue(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[2] = {10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newDampValue / base[digit]) % 10;
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
	newDampValue = newDampValue - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void SetDampValueKeyOptFun(uint8_t key)
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
				newDampValue = GetData(DAMP_ADDR);
				displayModel = SetDampValue;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveDampValue(void)
{
	// SAVE to FLASH
	UpdateData(DAMP_ADDR, newDampValue, TRUE);
}

void ChangeDampValuekeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateDampValue(ADD, SET_DAMP_VALUE_BASE);				
				break;
			case DOWN:
				UpdateDampValue(MINUS, SET_DAMP_VALUE_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveDampValueKeyOptFun(uint8_t key)
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
				SaveDampValue();			
				break;
			default:
				break;
		}
	
}

