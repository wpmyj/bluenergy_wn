#include "Include.h"
#include "Menu.h"
#include "Actuator.h"

extern uint8_t needRefresh;
extern void (*displayModel)(uint8_t);

void DisplaySetRelayStatus(void)
{

	DisplayOneLine16x16_with_params(4, 0, 4, "��ǰ״̬", FALSE);
	DisplayOne12x16(68, 0, ':', FALSE);
	DisplayOneLine16x16_with_params(80, 0, 1, ((GetRelayStatus() == OPEN) ? "��" : "��"), FALSE);
	DisplayOneLine16x16_with_params(4, 2, 1, "��", FALSE);
	DisplayOneLine12x16_with_params(22, 2, 1, "&", FALSE);
	DisplayOneLine16x16_with_params(37, 2, 1, "��", FALSE);
	DisplayOneLine16x16_with_params(56, 2, 1, "��", FALSE);

	DisplayOneLine16x16_with_params(4, 4, 1, "��", FALSE);
	DisplayOneLine12x16_with_params(22, 4, 1, "#", FALSE);
	DisplayOneLine16x16_with_params(37, 4, 1, "��", FALSE);
	DisplayOneLine16x16_with_params(56, 4, 1, "��", FALSE);

	DisplayOneLine16x16_with_params(99, 6, 2, "����", TRUE);	
}

void DisplayRelayStatusControlKeyOptFun(uint8_t key)
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
				SaveOptMod();
				MoveToNextMenu();
				ChangeDisplayMode(DisplaySetRelayStatus);
				break;
			default:
				break;
		}		

}

void SetRelayKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case UP:
				SetOptMod(MANUAL, DO_MOD);
				SetRelay(OPEN);
				break;
			case DOWN:
				SetOptMod(MANUAL, DO_MOD);
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

