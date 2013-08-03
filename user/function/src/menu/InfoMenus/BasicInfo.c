#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);

void GetInfoFromData(uint8_t baseAddr, uint8_t info[], uint8_t *length)
{
	uint8_t officeSet = 0;

	while(((Data[baseAddr + officeSet] != 0x00) || (Data[baseAddr + officeSet + 1] != 0x00)) && (officeSet < 16))
	{
		info[officeSet] = Data[baseAddr + officeSet];
		info[officeSet + 1] = Data[baseAddr + officeSet + 1];
		officeSet += 2;
		(*length)++;
	}
}

void GetDateFromData(uint8_t baseAddr, uint8_t info[])
{
	uint8_t i = 0;

	for(i = 0; i < 2; i++)
	{
		info[2 * i] = ((Data[baseAddr + i] >> 4) & 0x0f) + 48;
		info[2 * i + 1] = (Data[baseAddr + i] & 0x0f) + 48;
	}
}

void DisplayInfoBy16x16FromData(uint8_t baseAddr, uint8_t startX, uint8_t startY)
{
	uint8_t info[16];
	uint8_t  i = 0, length = 0;

	GetInfoFromData(baseAddr, info, &length);
	
	for(i = 0; i< length; i++)
	{
		DisplayOneLine16x16_with_params(startX, startY + i * 16, 1, &info[i * 2],FALSE);
	}
		
}

void DisplayInfoBy12x16FromData(uint8_t baseAddr, uint8_t startX, uint8_t startY)
{
	uint8_t info[16];
	uint8_t  i = 0, length = 0;

	GetInfoFromData(baseAddr, info, &length);
	
	for(i = 0; i< length; i++)
	{
		DisplayOneLine12x16_with_params(startX + 12 * i, startY, 1, &info[i * 2 + 1],FALSE);
	}

}

void DisplayDateBy12x16FromData(uint8_t baseAddr, uint8_t startX, uint8_t startY)
{
	uint8_t info[16];
	uint8_t  i = 0, length = 4;

	GetDateFromData(baseAddr, info);
	
	for(i = 0; i< length; i++)
	{
		DisplayOneLine12x16_with_params(startX + 12 * i, startY, 1, &info[i],FALSE);
	}

}

void DisplayDeviceStatus(void)
{
	DisplayOneLine16x16_with_params(4, 0, 6, "西安维纳测控", FALSE);
	
	DisplayOneLine16x16_with_params(4, 2, 2, "型号", FALSE);
	DisplayInfoBy12x16FromData(PRODUCT0_ADDR, 34, 2);
	
	DisplayOneLine16x16_with_params(4, 4, 2, "出厂", FALSE);
	DisplayDateBy12x16FromData(R_YEAR_ADDR, 34, 4);
	DisplayDateBy12x16FromData(R_DATE_ADDR, 82, 4);
	
	DisplayOneLine16x16_with_params(4, 6, 2, "检验", FALSE);
	DisplayDateBy12x16FromData(Q_YEAR_ADDR, 34, 6);
	DisplayDateBy12x16FromData(Q_DATE_ADDR, 82, 6);
}

void SubMenuEnterKeyOpt(void)
{
	currentMenu = menus[currentMenu].next;
	needRefresh = TRUE;
	displayModel = DisplayDeviceStatus;
	windowPointer = currentMenu;
}

void SubMenuKeyOptFun(uint8_t key)
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
				SubMenuEnterKeyOpt();
				break;
			default:
				break;
		}

}

