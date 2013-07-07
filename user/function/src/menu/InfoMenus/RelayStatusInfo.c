#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint8_t Data[];

void DisplayRelayStatusInfo(void)
{
	char buf[3] = {0, 0, 0};
	uint8_t currentMv;
	
	currentMv = (uint8_t)GetData(MV_ADDR); 
	sprintf( buf, "%3d", currentMv);

	DisplayOneLine16x16_with_params(4, 1, 3, "调节阀", FALSE);
	if(GetData(OCM_ADDR) == 0)
	{
		DisplayOneLine16x16_with_params(53, 1, 2, "正向", FALSE);
	}
	else 
	{
		DisplayOneLine16x16_with_params(53, 1, 2, "反向", FALSE);
	}	
	DisplayOneLine16x16_with_params(87, 1, 2, "控制", FALSE);
	DisplayOneLine16x16_with_params(4, 3, 2, "开度", FALSE);
	DisplayOneLine12x16_with_params(40, 3, 3, buf, FALSE);
	DisplayOne12x16(80, 3, '%', FALSE);	
}

void DisplayRelayStatusInfoKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayRelayStatusInfo);
				break;
			default:
				break;
		}

}

