#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint16_t Data[];

void DisplayCurrentOutput(void)
{
	char buf[5];
	float pp;
	
	pp = (float)GetData(CO_ADDR)/1000; 
	sprintf( buf, "%f", pp);
	DisplayOneLine12x16_with_params(14, 3, 2, "I:", FALSE);
	DisplayOneLine12x16_with_params(42, 3, 6, buf, FALSE);
	DisplayOneLine12x16_with_params(105, 3, 2, "MA", FALSE);
	
}

void DisplayCurrentOutputKeOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayCurrentOutput);
				break;
			default:
				break;
		}

}

