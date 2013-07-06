#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint8_t Data[];

void DisplayMeasureRange(void)
{
	char bufH[5], bufL[5];
	float rangeHigh, rangeLow;
	
	rangeHigh = (float)GetData(RH_ADDR)/1000; 
	sprintf( bufH, "%4.3f", rangeHigh);
	DisplayOneLine12x16_with_params(4, 2, 3, "RH:", FALSE);
	DisplayOneLine12x16_with_params(42, 2, 6, bufH, FALSE);
	DisplayOneLine12x16_with_params(105, 2, 1, "M", FALSE);

	rangeLow = (float)GetData(RL_ADDR)/1000; 
	sprintf( bufL, "%4.3f", rangeLow);
	DisplayOneLine12x16_with_params(4, 4, 3, "RL:", FALSE);
	DisplayOneLine12x16_with_params(42, 4, 6, bufL, FALSE);
	DisplayOneLine12x16_with_params(105, 4, 1, "M", FALSE);
	
}

void DisplayMeasureRangeKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayMeasureRange);
				break;
			default:
				break;
		}

}

