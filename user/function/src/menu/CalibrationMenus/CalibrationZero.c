#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);

void DisplayCalibrationZero(void)
{
	char value[4], preValue[4];

	sprintf( preValue, "%4d", GetData(CZ_ADDR));
	sprintf( value, "%4d", GetVINAdcValue());
	
	DisplayOneLine16x16_with_params(4, 0, 2, "设定值", FALSE); 
	DisplayOne12x16(40, 0, ':', FALSE);
	DisplayOneLine12x16_with_params(52, 0, 4, preValue, FALSE);
	
	DisplayOneLine16x16_with_params(4, 2, 2, "当前值", FALSE); 
	DisplayOne12x16(40, 2, ':', FALSE);
	DisplayOneLine12x16_with_params(52, 2, 4, value, FALSE);
	
	DisplayOneLine16x16_with_params(4, 4, 8, "请将浮球置于零位", FALSE);
	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 142) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 143) ? TRUE : FALSE);

}

void DisplayCalibrationZeroKeyOptFun(uint8_t key)
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
				displayModel = DisplayCalibrationZero;
				StartScreenRefreshTimer();
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveCalibrationZero(void)
{
	// SAVE to FLASH
	UpdateData(CZ_ADDR, GetVINAdcValue());
}

void SaveCalibrationZeroKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case DOWN:
				MoveToRightMenu();
				break;
			case ENTER:				
				SaveCalibrationZero();			
				break;
			default:
				break;
		}
	
}

