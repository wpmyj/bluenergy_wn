#include "Include.h"
#include "Menu.h"

void displayMainMenu(uint8_t y);

Menu mainManu = {NULL, NULL, "Î÷°²",  displayMainMenu};
Menu sub_1_Menu =  {NULL, NULL, "Î¬ÄÉ",  displayMainMenu};
extern Menu *currentMenu = NULL;

uint8_t isTopMenu(Menu *currentMenu);

void linkMenus(Menu *parent, Menu *child)
{
	parent->next = child;
	child->pre = parent;
}

void menuInit()
{
	currentMenu = &mainManu;
	linkMenus(&mainManu, &sub_1_Menu);
}

void displayMainMenu(uint8_t y)
{
	uint8_t test[6];	
	getNum(1099, 1, test);
	displayOneLine24x32_with_params(0, y, 5, test);	
}

void menuOperation(uint8_t selection)
{	
	currentMenu->optFun(4);
}

void menuModel()
{
	while(isTopMenu(currentMenu) == FALSE)
	{		
		menuOperation(4);
	}
}

void backToMainMenu(void)
{
	cleanScreen();
	TmrStop(MENU_TIMEOUT_TIMER);
}

void setMenuTimeoutTimer(void)
{
	TmrCfgFnct(FALSE, MENU_TIMEOUT_TIMER, backToMainMenu, (void *)0);
	TmrSetMST(MENU_TIMEOUT_TIMER, 0, 0, 100); 	
}

/* Private function */
bool isTopMenu(Menu *currentMenu)
{
	return (currentMenu->pre == NULL) ? TRUE : FALSE;
}