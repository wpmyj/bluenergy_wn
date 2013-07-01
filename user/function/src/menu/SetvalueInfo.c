#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern Data data;

void DisplaySetValue(void)
{
	char buf[100];
	float pp;
	GetData();
	pp = (float)data.SV/100; 
	sprintf( buf, "%f", pp);
	DisplayOneLine12x16_with_params(4, 3, 3, "SV:", FALSE);
	DisplayOneLine12x16_with_params(42, 3, 6, buf, FALSE);
	DisplayOneLine12x16_with_params(105, 3, 1, "M", FALSE);
	
}

void DisplaySetValeKeOptFun(uint8_t key)
{
	needRefresh = TRUE;
	switch(key)
		{
			case ENTER:
				MoveToNextMenu();
				StartScreenRefreshTimer();
				ChangeDisplayMode(DisplaySetValue);
				break;
			default:
				break;
		}

}
