#include "Include.h"
#include "Menu.h"

extern uint8_t needRefresh;

void SetOutputMode(void)
{
	if(GetData(OCM_ADDR) == 0)
	{		
		DisplayOne12x16(18, 0, '$', FALSE);
	}
	else if(GetData(OCM_ADDR) == 1)
	{		
		DisplayOne12x16(18, 3, '$', FALSE);
	}	
	DisplayOneLine16x16_with_params(30, 0, 5, "调节阀控制", FALSE);
	DisplayOneLine16x16_with_params(30, 3, 5, "电磁阀控制", FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", TRUE);
}

void SetOutputModeKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(SetOutputMode);
				MoveToNextMenu();				
				break;
			default:
				break;
		}			
}

void ChangeOutputModeKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
			
	switch(key)
		{
			case UP:
				UpdateData(OCM_ADDR, 0);
				break;
			case DOWN:
				UpdateData(OCM_ADDR, 1);
				break;
			case ENTER:				
				ChangeDisplayMode(DisplayMenu);
				MoveToNextMenu();	
				break;
			default:
				break;
		}			

}

