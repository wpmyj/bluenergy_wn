#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "SetP.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newP;

void SetP(void)
{
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE);
	DisplayOne12x16(40, 0, ((GetData(P_ADDR) / 100) % 10) + 48, FALSE);
	DisplayOne12x16(52, 0, ((GetData(P_ADDR) / 10) % 10) + 48, FALSE);
	DisplayOne12x16(64, 0, (GetData(P_ADDR) % 10) + 48, FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, ((newP / 100) % 10) + 48, 127);
	DisplayValueAndSimbol(52, 3, ((newP / 10) % 10) + 48, 128);
	DisplayValueAndSimbol(64, 3, (newP % 10) + 48, 129);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 130) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 131) ? TRUE : FALSE);

}

void UpdateP(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[3] = {100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newP / base[digit]) % 10;
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
	newP = newP - (digitValue  * base[digit]) + (singleValue * base[digit]);
	if(newP > 100)
	{
		newP = 100;
	}
}

void SetPKeyOptFun(uint8_t key)
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
				newP = GetData(P_ADDR);
				displayModel = SetP;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveP(void)
{
	// SAVE to FLASH
	UpdateData(P_ADDR, newP);
}

void ChangePkeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateP(ADD, SET_P_BASE);				
				break;
			case DOWN:
				UpdateP(MINUS, SET_P_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SavePKeyOptFun(uint8_t key)
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
				SaveP();			
				break;
			default:
				break;
		}
	
}

