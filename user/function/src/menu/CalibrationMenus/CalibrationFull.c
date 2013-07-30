#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#define CV_ADDR 128

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);

void DisplayCalibrationFull(void)
{
	char value[4], preValue[4];

	sprintf( preValue, "%4d", GetData(CV_ADDR));
	sprintf( value, "%4d", GetVINAdcValue());
	
	DisplayOneLine16x16_with_params(4, 0, 3, "设定值", FALSE); 
	DisplayOne12x16(52, 0, ':', FALSE);
	DisplayOneLine12x16_with_params(64, 0, 4, preValue, FALSE);
	
	DisplayOneLine16x16_with_params(4, 2, 3, "当前值", FALSE); 
	DisplayOne12x16(52, 2, ':', FALSE);
	DisplayOneLine12x16_with_params(64, 2, 4, value, FALSE);
	
	DisplayOneLine16x16_with_params(4, 4, 8, "请将浮球置于满位", FALSE);
	DisplayOneLine16x16_with_params(4, 6, 2, "保存", (currentMenu == 144) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(99, 6, 2, "返回", (currentMenu == 145) ? TRUE : FALSE);

}

void DisplayCalibrationFullKeyOptFun(uint8_t key)
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
				displayModel = DisplayCalibrationFull;
				StartScreenRefreshTimer();
				MoveToNextMenu();				
				break;
			default:
				break;
		}
	
}

void SaveCalibrationFull(void)
{
	// SAVE to FLASH
	UpdateData(CV_ADDR, GetVINAdcValue(), TRUE);
}

void SaveCalibrationFullKeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
		{
			case DOWN:
				MoveToRightMenu();
				break;
			case ENTER:				
				SaveCalibrationFull();			
				break;
			default:
				break;
		}
	
}

