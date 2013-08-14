#include "Include.h"
#include "Menu.h"
#include "Actuator.h"
#include "stdlib.h"
#include "SetValue.h"
#include "CalibrationValueHigh.h"

extern uint8_t currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);

void DisplayCalibrationZero(void)
{

	DisplayOneLine16x16_with_params(4, 0, 8, "将传感器置于零位", FALSE);
	DisplayOneLine16x16_with_params(4, 2, 6, "按确认键保存", FALSE);
	DisplayOneLine16x16_with_params(4, 4, 8, "按下一步满度校准", FALSE);
	DisplayOneLine16x16_with_params(4, 6, 2, "确认", (currentMenu == 142) ? TRUE : FALSE);
	DisplayOneLine16x16_with_params(83, 6, 3, "下一步", (currentMenu == 143) ? TRUE : FALSE);

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
	uint16_t currentADC_Value = GetVINAdcValue();
	
	UpdateData(ZR_ADDR, currentADC_Value, TRUE);
}

void SaveCalibrationZeroKeyOptFun(uint8_t key)
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
				SaveCalibrationZero();			
				break;
			default:
				break;
		}
	
}

void MoveToSetValueHighKeyOptFun(uint8_t key)
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
				displayModel = DisplayCalibrationValueHigh;
				MoveToNextMenu();	
				break;
			default:
				break;
		}
	
}

