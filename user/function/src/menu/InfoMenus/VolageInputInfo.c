#include "Include.h"
#include "Menu.h"

extern uint8_t needRefresh;
extern void (*displayModel)(uint8_t);

void DisplayVolageInputInfo(void)
{
	char buf[5];
	float currentVolage;
	
	currentVolage = (float)Convert_ADC_ValueToVolage(GetData(VI_ADDR))/1000; 
	sprintf( buf, "%4.3f", currentVolage);

	DisplayOneLine12x16_with_params(4, 3, 5, buf, FALSE);
	DisplayOneLine12x16_with_params(64, 3, 1, "v", FALSE);
	
}

void DisplayVolageInputInfoKeyOptFun(uint8_t key)
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
				StartScreenRefreshTimer();
				ChangeDisplayMode(DisplayVolageInputInfo);
				break;
			default:
				break;
		}

}

