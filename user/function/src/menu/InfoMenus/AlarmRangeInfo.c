#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint8_t Data[];

void DisplayAlarmRange(void)
{
	char bufH[5], bufL[5], bufHH[5], bufLL[5];
	float alarmRangeH,  alarmRangeL, alarmRangeHH, alarmRangeLL;
	
	alarmRangeHH = (float)GetData(AHH_ADDR)/1000; 
	sprintf( bufHH, "%4.3f", alarmRangeHH);
	DisplayOneLine12x16_with_params(4, 0, 3, "AHH:", FALSE);
	DisplayOneLine12x16_with_params(42, 0, 5, bufHH, FALSE);
	DisplayOneLine12x16_with_params(105, 0, 1, "M", FALSE);

	alarmRangeH = (float)GetData(AH_ADDR)/1000; 
	sprintf( bufH, "%4.3f", alarmRangeH);
	DisplayOneLine12x16_with_params(4, 2, 3, "AH:", FALSE);
	DisplayOneLine12x16_with_params(42, 2, 5, bufH, FALSE);
	DisplayOneLine12x16_with_params(105, 2, 1, "M", FALSE);

	alarmRangeL = (float)GetData(AL_ADDR)/1000; 
	sprintf( bufL, "%4.3f", alarmRangeL);
	DisplayOneLine12x16_with_params(4, 4, 3, "AL:", FALSE);
	DisplayOneLine12x16_with_params(42, 4, 5, bufL, FALSE);
	DisplayOneLine12x16_with_params(105, 4, 1, "M", FALSE);

	alarmRangeLL = (float)GetData(ALL_ADDR)/1000; 
	sprintf( bufLL, "%4.3f", alarmRangeLL);
	DisplayOneLine12x16_with_params(4, 6, 3, "ALL:", FALSE);
	DisplayOneLine12x16_with_params(42, 6, 5, bufLL, FALSE);
	DisplayOneLine12x16_with_params(105, 6, 1, "M", FALSE);
	
}

void DisplayAlarmRangeKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayAlarmRange);
				break;
			default:
				break;
		}

}

