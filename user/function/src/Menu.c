#include "Include.h"
#include "Menu.h"

void DisplayMainMenu(void);
void DisplayMenuWindow(uint8_t maxItemSize);
void ReturnBack(void);


Menu mainManu[5] = {{4, "��Ϣ��ѯ",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL}, 
								{4, "�˹�ģʽ",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL}, 
								{4, "��������",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL}, 
								{4, "ϵͳУ׼",  DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL},
								{2, "����",  	 DisplayMenuWindow, 5, TRUE, NULL, NULL, NULL, NULL}};

Menu sub_1_0_MenuItems[3] = {{4, "������Ϣ",  DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL},
						   	 {4, "���в���",  DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL},
						   	 {2, "����",  	DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL}};

Menu sub_1_0_3_MenuItems[1] = {{0, "",  ReturnBack, 1, TRUE, NULL, NULL, NULL, NULL}};


Menu sub_1_1_MenuItems[3] = {{5, "�̵�������",  DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL},
						   	 {4, "���ſ���",  DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL},
						   	 {2, "����",  	DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL}};

Menu sub_1_2_MenuItems[15] = {{6, "�������ģʽ",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "��������",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "��������",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "�澯����",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "�澯����",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {5, "�澯������",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {5, "�澯������",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "�趨Һλ",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {5, "����������",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "����ϵ��",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "��������",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "����ʱ��",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {4, "΢��ʱ��",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {5, "Һλ������",  DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL},
						   	  {2, "����",  	DisplayMenuWindow, 15, TRUE, NULL, NULL, NULL, NULL}};

Menu sub_1_3_MenuItems[3] = {{4, "���У׼",  DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL},
						   	 {4, "����У׼",  DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL},
						   	 {2, "����",  	DisplayMenuWindow, 3, TRUE, NULL, NULL, NULL, NULL}};

Menu *currentMenu = NULL;
Menu *slideWindowStart = NULL;

void ReturnBack(void)
{
	//currentMenu = currentMenu->pre;
}

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

void MenuInit()
{
	currentMenu = &mainManu[0];
	slideWindowStart = currentMenu;
	/* <<Top Menu Init>> */
	//<0>Top brothers init
	LinkBrotherMenu(&mainManu[0], mainManu[0].menuItemsNum);
	MenuItemsInit(&mainManu[0], mainManu[0].menuItemsNum);			

	/*<<<<<<<<<<<<<<<<<<<<<<<<< Sub Menu 1-0 Init>>>>>>>>>>>>>>>>>>>>>>>>> */
	//--0-- Link 1-0 to top 0
	LinkParentChildMenus(&mainManu[0], &sub_1_0_MenuItems[0]);
	
	//--1-- Sub 1-0 brothers init
	LinkBrotherMenu(&sub_1_0_MenuItems[0], sub_1_0_MenuItems[0].menuItemsNum);
	MenuItemsInit(&sub_1_0_MenuItems[0], sub_1_0_MenuItems[0].menuItemsNum);

	/*<<<<<<<<<<<<<<<<<<<<<<<<< Sub Menu 1-0 [3] Init>>>>>>>>>>>>>>>>>>>>>>>>> */
	//--0-- Link 1-0-3 to sub 1-0 [3] 
	LinkParentChildMenus(&sub_1_0_MenuItems[3], &sub_1_0_3_MenuItems[0]);
	LinkParentChildMenus(&sub_1_0_3_MenuItems[0], &mainManu[0]);

	/*<<<<<<<<<<<<<<<<<<<<<<<<< Sub Menu 1-1 Init>>>>>>>>>>>>>>>>>>>>>>>>> */
	//--0-- Link 1-1 to top 1
	LinkParentChildMenus(&mainManu[1], &sub_1_1_MenuItems[0]);
	
	//--1-- Sub 1-1 brothers init
	LinkBrotherMenu(&sub_1_1_MenuItems[0], sub_1_1_MenuItems[0].menuItemsNum);
	MenuItemsInit(&sub_1_1_MenuItems[0], sub_1_1_MenuItems[0].menuItemsNum);

	/*<<<<<<<<<<<<<<<<<<<<<<<<< Sub Menu 1-2 Init>>>>>>>>>>>>>>>>>>>>>>>>> */
	//--0-- Link 1-2 to top 2
	LinkParentChildMenus(&mainManu[2], &sub_1_2_MenuItems[0]);
	
	//--1-- Sub 1-2 brothers init
	LinkBrotherMenu(&sub_1_2_MenuItems[0], sub_1_2_MenuItems[0].menuItemsNum);
	MenuItemsInit(&sub_1_2_MenuItems[0], sub_1_2_MenuItems[0].menuItemsNum);

	/*<<<<<<<<<<<<<<<<<<<<<<<<< Sub Menu 1-3 Init>>>>>>>>>>>>>>>>>>>>>>>>> */
	//--0-- Link 1-3 to top 3
	LinkParentChildMenus(&mainManu[3], &sub_1_3_MenuItems[0]);
	
	//--1-- Sub 1-3 brothers init
	LinkBrotherMenu(&sub_1_3_MenuItems[0], sub_1_3_MenuItems[0].menuItemsNum);
	MenuItemsInit(&sub_1_3_MenuItems[0], sub_1_3_MenuItems[0].menuItemsNum);

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
			isSelected = (p == currentMenu) ? TRUE : FALSE;

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

