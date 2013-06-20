#include "Include.h"
#include "Menu.h"

void displayMainMenu(void);
void displaySubMenu(void);
uint8_t menuSize[3] = {2, 15};

Menu mainManu = {NULL, NULL, TRUE, 0, 2, "Î÷°²",  displayMainMenu};
Menu sub_1_MenuItems[2] = {{NULL, NULL, TRUE, 0, 2, "Î¬ÄÉ",  displaySubMenu}, {NULL, NULL, TRUE, 1, 2, "²â¿Ø",  displaySubMenu}};
Menu sub_2_MenuItems[2] = {{NULL, NULL, TRUE, 0, 1, "Î¬",  displaySubMenu}, {NULL, NULL, TRUE, 1, 1, "¿Ø",  displaySubMenu}};

extern Menu *currentMenu = NULL;

uint8_t isTopMenu(Menu *currentMenu);

void linkParentChildMenus(Menu *parent, Menu *child)
{
	parent->next = child;
	child->pre = parent;
}

void menuItemsInit(Menu *menuItems, uint8_t size)
{
	uint8_t i = 0;

	for(i = 0; i < (size - 1); i++)
	{
		menuItems[i].pre= menuItems[i + 1].pre;
		menuItems[i].next = menuItems[i + 1].next;
	}
}

void menuInit()
{
	currentMenu = &mainManu;
	linkParentChildMenus(&mainManu, &sub_1_MenuItems[0]);
	linkParentChildMenus(&sub_1_MenuItems[0], &sub_2_MenuItems[0]);
	menuItemsInit(&sub_1_MenuItems[0], 2);
}

void displaySubMenu(void)
{	
	uint8_t i = 0;
	bool isSelected = FALSE;
	
	if(currentMenu->refresh == TRUE)
	{
		cleanScreen();
		for(i = 0; (i < MENU_WINDOW_SIZE) && (i < menuSize[0]); i++)
		{
			isSelected = (currentMenu[i].position == i) ? TRUE : FALSE;

			displayOneLine16x16_with_params(0, i * 2, currentMenu[i].displayContentLength, currentMenu[i].displayContent, isSelected);
		}
		currentMenu->refresh = FALSE;
	}		
}

void displayMainMenu(void)
{
	uint8_t hight[6];	
	if(currentMenu->refresh == TRUE)
	{
		getNum(1099, 2, hight);
		displayOneLine24x32_with_params(0, 2, 5, hight);	
		currentMenu->refresh = FALSE;
	}
}

void menuOperation(void)
{	
	currentMenu->optFun(0);
}

void menuModel()
{
	menuOperation();
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