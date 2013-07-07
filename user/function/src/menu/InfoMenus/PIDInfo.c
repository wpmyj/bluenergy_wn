#include "Include.h"
#include "Menu.h"

extern const Menu menus[];
extern uint8_t windowPointer, currentMenu, needRefresh;
extern void (*displayModel)(uint8_t);
extern uint8_t Data[];

void DisplayPID_Info(void)
{
	char bufP[3], bufI[3], bufD[3];
	uint8_t p,  i, d;
	
	p = (uint8_t)GetData(P_ADDR); 
	sprintf( bufP, "%3d", p);
	DisplayOneLine12x16_with_params(4, 0, 2, "P:", FALSE);
	DisplayOneLine12x16_with_params(30, 0, 3, bufP, FALSE);

	i = (uint8_t)GetData(I_ADDR); 
	sprintf( bufI, "%3d", i);
	DisplayOneLine12x16_with_params(4, 2, 2, "I:", FALSE);
	DisplayOneLine12x16_with_params(30, 2, 3, bufI, FALSE);

	d = (uint8_t)GetData(D_ADDR); 
	sprintf( bufD, "%3d", d);
	DisplayOneLine12x16_with_params(4, 4, 2, "D:", FALSE);
	DisplayOneLine12x16_with_params(30, 4, 3, bufD, FALSE);
	
}

void DisplayPID_InfoKeyOptFun(uint8_t key)
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
				ChangeDisplayMode(DisplayPID_Info);
				break;
			default:
				break;
		}

}

