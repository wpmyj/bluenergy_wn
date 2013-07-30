#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "SetValue.h"
#include "RegulatingValveControl.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint16_t newRegulatingValveValue;

void SetValveValue(void)
{
	char value[3], preValue[3];
	preValue[0] = ((newRegulatingValveValue / 100) % 10) + 48;
	preValue[1] = ((newRegulatingValveValue / 10) % 10) + 48;
	preValue[2] = (newRegulatingValveValue % 10) + 48;
	value[0] = ((GetData(MV_ADDR) / 100) % 10) + 48;
	value[1] = ((GetData(MV_ADDR) / 10) % 10) + 48;
	value[2] = (GetData(MV_ADDR) % 10) + 48;
	
	DisplayOneLine16x16_with_params(4, 0, 4, "当前开度", FALSE);
	DisplayOne12x16(68, 0, ':', FALSE);
	DisplayOneLine12x16_with_params(80, 0, 3, value, FALSE);
	DisplayOne12x16(116, 0, '%', FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 4, "设定开度", FALSE);
	DisplayOne12x16(68, 3, ':', FALSE);
	DisplayValueAndSimbol(80, 3, preValue[0], 67);
	DisplayValueAndSimbol(92, 3, preValue[1], 68);
	DisplayValueAndSimbol(104, 3, preValue[2], 69);
	DisplayOne12x16(116, 3, '%', FALSE);
	DisplayOneLine16x16_with_params(4, 6, 2, "执行", (currentMenu == 70) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 71) ? TRUE : FALSE);

}

void DisplayValveControlKeyOptFun(uint8_t key)
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
				SaveOptMod();
				SetOptMod(MANUAL, AO_MOD);
				newRegulatingValveValue = GetData(MV_ADDR);
				ChangeDisplayMode(SetValveValue);
				MoveToNextMenu();				
				break;
			default:
				break;
		}		

}

void SaveValveValue(void)
{
	// SAVE to FLASH
	UpdateData(MV_ADDR, newRegulatingValveValue, FALSE);
}

void UpdateValveValue(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[3] = {100, 10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newRegulatingValveValue / base[digit]) % 10;
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
	newRegulatingValveValue = newRegulatingValveValue - (digitValue  * base[digit]) + (singleValue * base[digit]);
	if(newRegulatingValveValue > 100)
	{
		newRegulatingValveValue = 100;
	}
}

void ChangeValveValueKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateValveValue(ADD, SET_VALVE_VALUE_BASE);				
				break;
			case DOWN:
				UpdateValveValue(MINUS, SET_VALVE_VALUE_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveValveValueKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				MoveToLeftMenu();
				//MoveToFirstValueMenuItem(SET_VALVE_VALUE_BASE);
				break;
			case DOWN:
				MoveToRightMenu();
				break;
			case ENTER:				
				SaveValveValue();			
				break;
			default:
				break;
		}
	
}

