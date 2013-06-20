#include "Include.h"
#include "Menu.h"

void displayMainMenu(uint8_t y);
int testing = 0;
Menu manu = {"≤‚ ‘",  displayMainMenu};

uint8_t isTopMenu(void);
void displayMainMenu(uint8_t y)
{
	uint8_t test[6];
	
	getNum(1099, 1, test);
	displayOneLine24x32_with_paras(0, y, 5, test);	
}

void menuOperation(uint8_t selection)
{	
	//manu.optFun(4);
}

void menuModel()
{
	//while(!isTopMenu())
	{
		
		if(testing == 0)
		{
			menuOperation(4);
		}
	}
}

void backToMainMenu(void)
{
	cleanScreen();
	testing = 1;
	TmrStop(MENU_TIMEOUT_TIMER);
}

void setMenuTimeoutTimer(void)
{
	TmrCfgFnct(FALSE, MENU_TIMEOUT_TIMER, backToMainMenu, (void *)0);
	TmrSetMST(MENU_TIMEOUT_TIMER, 0, 0, 100); 	
}

/* Private function */
bool isTopMenu(void)
{
	return (0) ? TRUE : FALSE;
}