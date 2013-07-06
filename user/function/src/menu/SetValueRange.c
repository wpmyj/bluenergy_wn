#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint8_t Data[];

void DisplaySetValueRange(void)
{
	char buf[5];
	float pp;
	
	pp = (float)GetData(SVH_ADDR)/1000; 
	sprintf( buf, "%4.3f", pp);
	DisplayOneLine12x16_with_params(14, 2, 4, "SVH:", FALSE);
	DisplayOneLine12x16_with_params(50, 2, 6, buf, FALSE);
	DisplayOneLine12x16_with_params(112, 2, 1, "M", FALSE);

	pp = (float)GetData(SVL_ADDR)/1000; 
	sprintf( buf, "%4.3f", pp);
	DisplayOneLine12x16_with_params(14, 4, 4, "SVL:", FALSE);
	DisplayOneLine12x16_with_params(50, 4, 6, buf, FALSE);
	DisplayOneLine12x16_with_params(112, 4, 1, "M", FALSE);
	
}

void DisplaySetValueRangeKeOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplaySetValueRange);
				break;
			default:
				break;
		}

}

