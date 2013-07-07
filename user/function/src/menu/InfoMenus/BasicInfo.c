#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);

void DisplayDeviceStatus(void)
{
	DisplayOneLine16x16_with_params(4, 0, 6, "西安维纳测控", FALSE);
	
	DisplayOneLine16x16_with_params(4, 2, 2, "型号", FALSE);
	DisplayOneLine12x16_with_params(34, 2, 6, "WINNER", FALSE);
	
	DisplayOneLine16x16_with_params(4, 4, 2, "出厂", FALSE);
	DisplayOneLine12x16_with_params(34, 4, 4, "2013", FALSE);
	DisplayOneLine12x16_with_params(82, 4, 2, "07", FALSE);
	DisplayOneLine12x16_with_params(106, 4, 2, "01", FALSE);
	
	DisplayOneLine16x16_with_params(4, 6, 2, "检验", FALSE);
	DisplayOneLine12x16_with_params(34, 6, 4, "2013", FALSE);
	DisplayOneLine12x16_with_params(82, 6, 2, "07", FALSE);
	DisplayOneLine12x16_with_params(106, 6, 2, "01", FALSE);

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
