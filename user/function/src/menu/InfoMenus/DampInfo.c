#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint8_t Data[];

void DisplayDampInfo(void)
{
	char buf[2] = {0, 0};
	uint8_t currentDamp;
	
	currentDamp = (uint8_t)GetData(DAMP_ADDR); 
	sprintf( buf, "%2d", currentDamp);
	
	DisplayOneLine16x16_with_params(4, 0, 4, "Êý×ÖÂË²¨", FALSE);	
	DisplayOneLine16x16_with_params(4, 2, 2, "Ê±¼ä", FALSE);	
	DisplayOne12x16(36, 2, ':', FALSE);

	DisplayOneLine12x16_with_params(50, 2, 2, buf, FALSE);	

	DisplayOne12x16(74, 2, 's', FALSE);
}

void DisplayDampInfoKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayDampInfo);
				break;
			default:
				break;
		}

}

