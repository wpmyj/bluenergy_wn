#include "Include.h"
#include "Menu.h"
#include "Actuator.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint16_t Data[];

void DisplaySetRelayStatus(void)
{

	DisplayOneLine16x16_with_params(4, 0, 2, "当前", FALSE);
	DisplayOneLine16x16_with_params(40, 0, 1, ((GetRelayStatus() == OPEN) ? "开" : "关"), FALSE);
	DisplayOneLine16x16_with_params(4, 2, 1, "按", FALSE);
	DisplayOneLine12x16_with_params(22, 2, 1, "&", FALSE);
	DisplayOneLine16x16_with_params(37, 2, 1, "键", FALSE);
	DisplayOneLine16x16_with_params(56, 2, 1, "开", FALSE);

	DisplayOneLine16x16_with_params(4, 4, 1, "按", FALSE);
	DisplayOneLine12x16_with_params(22, 4, 1, "#", FALSE);
	DisplayOneLine16x16_with_params(37, 4, 1, "键", FALSE);
	DisplayOneLine16x16_with_params(56, 4, 1, "关", FALSE);

	DisplayOneLine16x16_with_params(99, 6, 2, "返回", TRUE);	
}

void DisplaySetRelayStatusKeOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				UpKeyOpt();
				break;
			case DOWN:
				DownKeyOpt();
				break;
			case ENTER:
				SaveOptMod();
				MoveToNextMenu();
				ChangeDisplayMode(DisplaySetRelayStatus);
				break;
			default:
				break;
		}		

}

void SetRelayKeOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				SetOptMod(MANUAL);
				SetRelay(OPEN);
				break;
			case DOWN:
				SetOptMod(MANUAL);
				SetRelay(CLOSE);
				break;
			case ENTER:
				displayModel = DisplayMenu;
				RestoreOptMod();
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

