#include "Include.h"
#include "Menu.h"

extern uint8_t needRefresh;
extern void (*displayModel)(uint8_t);

void DisplayDeviceAddr(void)
{
	char buf[2];

	sprintf( buf, "%2d", GetData(DA_ADDR));
	DisplayOneLine16x16_with_params(4, 4, 4, "…Ë±∏µÿ÷∑", FALSE);	
	DisplayOne12x16(68, 4, ':', FALSE);
	DisplayOneLine12x16_with_params(80, 4, 2, buf, FALSE);	
}

void DisplayDeviceAddrKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayDeviceAddr);
				break;
			default:
				break;
		}

}

