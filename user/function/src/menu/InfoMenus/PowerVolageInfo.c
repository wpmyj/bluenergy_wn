#include "Include.h"
#include "Menu.h"
#include "Adc.h"

extern uint8_t needRefresh;
extern void (*displayModel)(uint8_t);

uint16_t Convert_ADC_ValueTo_24V_Volage(uint16_t raw)
{
	long tmp;
	tmp = (long)raw * 24000;
	return (uint16_t)(tmp / 4095);	
}

void DisplayPowerVolageInfo(void)
{
	char buf[5];
	float currentVolage;
	
	currentVolage = (float)Convert_ADC_ValueTo_24V_Volage(GetPowerAdcValue())/1000; 
	sprintf( buf, "%4.3f", currentVolage);

	DisplayOneLine12x16_with_params(4, 3, 5, buf, FALSE);
	DisplayOneLine12x16_with_params(64, 3, 1, "V", FALSE);
	
}

void DisplayPowerVolageInfoKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayPowerVolageInfo);
				break;
			default:
				break;
		}

}

