#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "SetDeviceAddr.h"

extern const Menu menus[];
extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
uint8_t newSetDeviceAddrValue;

void SetDeviceAddr(void)
{
	char value[2], preValue[2];
	preValue[0] = ((newSetDeviceAddrValue / 10) % 10) + 48;
	preValue[1] = (newSetDeviceAddrValue % 10) + 48;
	value[0] = (deviceAddr / 10) + 48;
	value[1] = (deviceAddr % 10) + 48;
	
	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE);
	DisplayOne12x16(36, 0, ':', FALSE);
	DisplayOneLine12x16_with_params(48, 0, 2, value, FALSE);
	
	DisplayOneLine16x16_with_params(4, 3, 4, "设备地址", FALSE);
	DisplayOne12x16(68, 3, ':', FALSE);
	DisplayValueAndSimbol(80, 3, preValue[0], 63);
	DisplayValueAndSimbol(92, 3, preValue[1], 64);

	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 65) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 66) ? TRUE : FALSE);

}

void SetDeviceAddrKeyOptFun(uint8_t key)
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
				newSetDeviceAddrValue = deviceAddr;
				ChangeDisplayMode(SetDeviceAddr);
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveDeviceAddr(void)
{
	// SAVE to FLASH
	deviceAddr = newSetDeviceAddrValue;
}

void UpdateDeviceAddr(uint8_t how, uint8_t baseMenu)
{
	uint16_t base[2] = {10, 1};
	uint8_t digit = currentMenu - baseMenu;
	uint16_t digitValue = (newSetDeviceAddrValue / base[digit]) % 10;
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
	newSetDeviceAddrValue = newSetDeviceAddrValue - (digitValue  * base[digit]) + (singleValue * base[digit]);
}

void ChangeDeviceAddrKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpdateDeviceAddr(ADD, SET_DEVICE_ADDR_BASE);				
				break;
			case DOWN:
				UpdateDeviceAddr(MINUS, SET_DEVICE_ADDR_BASE);				
				break;
			case ENTER:				
				MoveToRightMenu();
				break;
			default:
				break;
		}
	
}

void SaveDeviceAddrKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				MoveToFirstValueMenuItem(SET_DEVICE_ADDR_BASE);
				break;
			case DOWN:
				MoveToRightMenu();
				break;
			case ENTER:				
				SaveDeviceAddr();			
				break;
			default:
				break;
		}
	
}

