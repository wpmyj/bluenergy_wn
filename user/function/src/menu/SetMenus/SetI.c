#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "SetI.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newI;

void SetI(void)
{
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE);
	DisplayOne12x16(40, 0, ((GetData(I_ADDR) / 100) % 10) + 48, FALSE);
	DisplayOne12x16(52, 0, ((GetData(I_ADDR) / 10) % 10) + 48, FALSE);
	DisplayOne12x16(64, 0, (GetData(I_ADDR) % 10) + 48, FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 2, "设定", FALSE);
	DisplayValueAndSimbol(40, 3, ((newI / 100) % 10) + 48, 132);
	DisplayValueAndSimbol(52, 3, ((newI / 10) % 10) + 48, 133);
	DisplayValueAndSimbol(64, 3, (newI % 10) + 48, 134);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 135) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 136) ? TRUE : FALSE);

}

void UpdateI(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[3] = {100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newI / base[digit]) % 10;
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
	newI = newI - (digitValue  * base[digit]) + (singleValue * base[digit]);
	if(newI > 100)
	{
		newI = 100;
	}
}

void SetIKeyOptFun(uint8_t key)
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
				newI = GetData(I_ADDR);
				displayModel = SetI;
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveI(void)
{
	// SAVE to FLASH
	UpdateData(I_ADDR, newI, TRUE);
}

void ChangeIkeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateI(ADD, SET_I_BASE);				
				break;
			case DOWN:
				UpdateI(MINUS, SET_I_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveIKeyOptFun(uint8_t key)
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
				SaveI();			
				break;
			default:
				break;
		}
	
}

