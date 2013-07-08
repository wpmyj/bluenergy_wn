#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "SetD.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newD;

void SetD(void)
{
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE);
	DisplayOne12x16(40, 0, ((GetData(D_ADDR) / 100) % 10) + 48, FALSE);
	DisplayOne12x16(52, 0, ((GetData(D_ADDR) / 10) % 10) + 48, FALSE);
	DisplayOne12x16(64, 0, (GetData(D_ADDR) % 10) + 48, FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, ((newD / 100) % 10) + 48, 137);
	DisplayValueAndSimbol(52, 3, ((newD / 10) % 10) + 48, 138);
	DisplayValueAndSimbol(64, 3, (newD % 10) + 48, 139);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 140) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 141) ? TRUE : FALSE);

}

void UpdateD(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[3] = {100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newD / base[digit]) % 10;
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
	newD = newD - (digitValue  * base[digit]) + (singleValue * base[digit]);
	if(newD > 100)
	{
		newD = 100;
	}
}

void SetDKeyOptFun(uint8_t key)
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
				newD = GetData(D_ADDR);
				displayModel = SetD;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveD(void)
{
	// SAVE to FLASH
	UpdateData(D_ADDR, newD);
}

void ChangeDkeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateD(ADD, SET_D_BASE);				
				break;
			case DOWN:
				UpdateD(MINUS, SET_D_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveDKeyOptFun(uint8_t key)
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
				SaveD();			
				break;
			default:
				break;
		}
	
}

