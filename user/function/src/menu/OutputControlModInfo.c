#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint8_t Data[];

void DisplayOutputControlModInfo(void)
{
		
	if(GetData(OCM_ADDR) == 0)
	{
		DisplayOneLine16x16_with_params(30, 2, 5, "电磁阀控制", FALSE);	
		//DisplayOne12x16(18, 2, '$', FALSE);
	}
	else if(GetData(OCM_ADDR) == 1)
	{
		DisplayOneLine16x16_with_params(30, 5, 4, "自动控制", FALSE);
		//DisplayOne12x16(18, 5, '$', FALSE);
	}	
}

void DisplayOutputControlModInfoKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayOutputControlModInfo);
				break;
			default:
				break;
		}

}

