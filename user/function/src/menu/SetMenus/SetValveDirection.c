#include "Include.h"
#include "Menu.h"

extern uint8_t needRefresh;

void SetValveDirection(void)
{
	if(GetData(AOFR_ADDR) == 0)
	{		
		DisplayOne12x16(18, 0, '$', FALSE);
	}
	else if(GetData(AOFR_ADDR) == 1)
	{		
		DisplayOne12x16(18, 3, '$', FALSE);
	}	
	DisplayOneLine16x16_with_params(30, 0, 2, "正向", FALSE);
	DisplayOneLine16x16_with_params(30, 3, 2, "反向", FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", TRUE);
}

void SetValveDirectionKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(SetValveDirection);
				MoveToNextMenu();				
				break;
			default:
				break;
		}			
}

void ChangeValveDirectionKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
			
	switch(key)
		{
			case UP:
				UpdateData(AOFR_ADDR, 0);
				break;
			case DOWN:
				UpdateData(AOFR_ADDR, 1);
				break;
			case ENTER:				
				ChangeDisplayMode(DisplayMenu);
				MoveToNextMenu();	
				break;
			default:
				break;
		}			

}

