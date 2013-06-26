#include "Include.h"
#include "Menu.h"

#define		TOP_MENU_SIZE	5
#define		SUB_1_MENU_SIZE	2
#define		SUB_2_MENU_SIZE	2



void DisplayMainMenu(void);
void DisplayMenuWindow(uint8_t maxItemSize);

Menu mainManu[TOP_MENU_SIZE] = {{0, 1, "Î÷",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL}, 
								{1, 1, "°²",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL}, 
								{2, 1, "Î¬",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL}, 
								{3, 1, "ÄÉ",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL},
								{4, 1, "²â",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL}};

Menu sub_1_MenuItems[SUB_1_MENU_SIZE] = {{0, 2, "Î¬ÄÉ",  DisplayMenuWindow, 2, TRUE, NULL, NULL, NULL, NULL},
						   				 {1, 2, "²â¿Ø",  DisplayMenuWindow, 2, TRUE, NULL, NULL, NULL, NULL}};

Menu sub_2_MenuItems[SUB_2_MENU_SIZE] = {{0, 1, "²â",  DisplayMenuWindow, 2, TRUE, NULL, NULL, NULL, NULL}, 
						   				 {1, 1, "¿Ø",  DisplayMenuWindow, 2, TRUE, NULL, NULL, NULL, NULL}};

Menu *currentMenu = NULL;
Menu *slideWindowStart = NULL;

void LinkParentChildMenus(Menu *parent, Menu *child)
{
	parent->next = child;
	child->pre = parent;
}

void LinkBrotherMenu(Menu *current, uint8_t menuSize)
{
	uint8_t i = 0;

	do {
		current[i].left = (i == 0) ? (&current[menuSize - 1]) : (&current[i - 1]);
		current[i].right = (i == menuSize - 1) ? (&current[0]) : (&current[i + 1]);
	} while(++i < menuSize);
}

void MenuItemsInit(Menu *menuItems, uint8_t menuSize)
{
	uint8_t i = 0;
	
	do {
		menuItems[i + 1].pre= menuItems[i].pre;
	} while(++i < menuSize);
}

void MenuTreeInit()
{
	
}

void MenuInit()
{
	currentMenu = &mainManu[0];
	slideWindowStart = currentMenu;
	//Top Menu Init
	LinkParentChildMenus(&mainManu[0], &sub_1_MenuItems[0]);
	LinkBrotherMenu(&mainManu[0], TOP_MENU_SIZE);
	MenuItemsInit(&mainManu[0], TOP_MENU_SIZE);
	
	//Sub Menu 1 Init
	LinkParentChildMenus(&sub_1_MenuItems[0], &sub_2_MenuItems[0]);
	LinkBrotherMenu(&sub_1_MenuItems[0], SUB_1_MENU_SIZE);
	MenuItemsInit(&sub_1_MenuItems[0], SUB_1_MENU_SIZE);

	//Sub Menu 2 Init	
	LinkBrotherMenu(&sub_2_MenuItems[0], SUB_2_MENU_SIZE);
	MenuItemsInit(&sub_2_MenuItems[0], SUB_2_MENU_SIZE);
}

void DisplayMenuWindow(uint8_t maxItemSize)
{	
	uint8_t i = 0;
	bool isSelected = FALSE;
	Menu *p = slideWindowStart;
	
	if(currentMenu->refresh == TRUE)
	{
		CleanScreen();
		for(i = 0; (i < MENU_WINDOW_SIZE) && (i < maxItemSize); i++)
		{
			isSelected = (currentMenu->position == p->position) ? TRUE : FALSE;

			DisplayOneLine16x16_with_params(4, i * 2, p->displayContentLength, p->displayContent, isSelected);

			p = p->right;
		}
		currentMenu->refresh = FALSE;
	}		
}

void DisplayMainMenu(void)
{
	uint8_t hight[6];	
	if(currentMenu->refresh == TRUE)
	{
		GetNum(1099, 2, hight);
		DisplayOneLine24x32_with_params(4, 2, 5, hight);	
		currentMenu->refresh = FALSE;
	}
}

void MenuOperation(void)
{	
	currentMenu->optFun(currentMenu->menuItemsNum);
}

void MenuModel()
{
	MenuOperation();
}

void BackToMainMenu(void)
{
	CleanScreen();
	TmrStop(MENU_TIMEOUT_TIMER);
}

void SetMenuTimeoutTimer(void)
{
	TmrCfgFnct(FALSE, MENU_TIMEOUT_TIMER, BackToMainMenu, (void *)0);
	TmrSetMST(MENU_TIMEOUT_TIMER, 0, 0, 100); 	
}

/* Private function */

