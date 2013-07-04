#include "Include.h"
#include "SubMenus.h"
#include "Menu.h"

extern uint8_t windowPointer = 0, currentMenu = 0, needRefresh = TRUE;
extern void (*displayModel)(uint8_t);

extern const Menu menus[53] = {{4, "��Ϣ��ѯ",  KeyOptFun, 5, 4, 1}, 	// 0
					 {4, "�˹�ģʽ",  KeyOptFun, 8, 0, 2}, 				// 1 
					 {4, "��������",  KeyOptFun, 11, 1, 3}, 				// 2 
					 {4, "ϵͳУ׼",  KeyOptFun, 26, 2, 4}, 				// 3
					 {2, "����",  	 ReturnToMainWindowKeyOptFun, 0, 3, 0}, // 4
					 
					 {4, "������Ϣ",  SubMenuKeyOptFun, 41, 7, 6}, 		// 5
					 {4, "���в���",  KeyOptFun, 29, 5, 7}, 			// 6
					 {2, "����",  	KeyOptFun, 0, 6, 5}, 				// 7
					 
					 {5, "��ŷ�����",  DisplaySetRelayStatusKeOptFun, 42, 10, 9}, // 8
					 {5, "���ڷ�����",  KeyOptFun, NULL, 8, 10}, 			// 9
					 {2, "����",  	KeyOptFun,0, 9, 8}, 				// 10
					 
					 {6, "�������ģʽ",  KeyOptFun, NULL, 25, 12}, 	// 11
					 {4, "��������",  KeyOptFun, NULL, 11, 13}, 		// 12
					 {4, "��������",  KeyOptFun, NULL, 12, 14}, 		// 13
					 {4, "�澯����",  KeyOptFun, NULL, 13, 15}, 		// 14
					 {4, "�澯����",  KeyOptFun, NULL, 14, 16}, 		// 15
					 {5, "�澯������",  KeyOptFun, NULL, 15, 17}, 		// 16
					 {5, "�澯������",  KeyOptFun, NULL, 16, 18}, 		// 17
					 {4, "�趨Һλ",  SetValueKeOptFun, 44, 17, 19}, 	// 18
					 {5, "����������",  KeyOptFun, NULL, 18, 20}, 		// 19
					 {4, "����ϵ��",  KeyOptFun, NULL, 19, 21}, 		// 20
					 {4, "��������",  KeyOptFun, NULL, 20, 22}, 		// 21
					 {4, "����ʱ��",  KeyOptFun, NULL, 21, 23}, 		// 22
					 {4, "΢��ʱ��",  KeyOptFun, NULL, 22, 24}, 		// 23
					 {5, "Һλ������",  KeyOptFun, NULL, 23, 25}, 		// 24
					 {2, "����",  	KeyOptFun, NULL, 24, 11}, 			// 25
					 
					 {4, "���У׼",  KeyOptFun, NULL, 28, 27}, 		// 26
					 {4, "����У׼",  KeyOptFun, NULL, 26, 28}, 		// 27
					 {2, "����",	 KeyOptFun, NULL, 27, 26}, 			// 28
					 
					 {6, "�������ģʽ",	 KeyOptFun, NULL, 40, 30}, 	// 29
					 {4, "���̷�Χ",	 KeyOptFun, NULL, 29, 31}, 		// 30
					 {4, "�澯��Χ",	 KeyOptFun, NULL, 30, 32}, 		// 31		
					 {4, "�趨Һλ",	 DisplaySetValeKeOptFun, 50, 31, 33}, // 32
					 {4, "����״̬",	 KeyOptFun, NULL, 32, 34}, 		// 33
					 {4, "����ϵ��",	 KeyOptFun, NULL, 33, 35}, 		// 34		
					 {5, "Ƥ����ϵ��",	 KeyOptFun, NULL, 34, 36}, 			// 35		
					 {4, "�������",	 DisplayCurrentOutputKeOptFun, 51, 35, 37}, 	// 36
					 {4, "��ѹ����",	 KeyOptFun, NULL, 36, 38}, 		// 37
					 {4, "��Դ��ѹ",	 KeyOptFun, NULL, 37, 39}, 		// 38
					 {6, "Һλ�趨��Χ", DisplaySetValueRangeKeOptFun, 52, 38, 40}, 	// 39
					 {2, "����",	 KeyOptFun, NULL,     39, 29}, 		// 40
			
					 {0, "",	 ReturnToSubMenuKeyOptFun, 5, 41, 41}, 	// 41  	������Ϣ

					 {2, "����",  SetRelayKeOptFun, 8, 42, 42}, 			// 42 	�̵�������
					 
					 {0, "",	 ReturnToSubMenuKeyOptFun, 9, 43, 43}, 	// 43	���ſ���

					  // ���в��� - �趨Һλ��ѯ

				   	 {1, "",	 ChangeValueKeOptFun, 18, 47, 45},	//44		Һλ����1 λ

					 {1, "",	 ChangeValueKeOptFun, 18, 44, 46},	//45		ҺλС��1 λ

					 {1, "",	 ChangeValueKeOptFun, 18, 45, 47},	//46		ҺλС��2 λ

					 {1, "",	 ChangeValueKeOptFun, 18, 46, 48},	//47		ҺλС��3 λ

					 {2, "����",	 SaveValueKeOptFun, 18, 47, 49},	//48		Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 18, 48, 44}, //49		Һλ����

					 {2, "����",	 ReturnToSubMenuKeyOptFun, 32, 50, 50},	//50		Һλ����

					 {2, "����",	 ReturnToSubMenuKeyOptFun, 36, 51, 51},	//51		Һλ����

					 {2, "����",	 ReturnToSubMenuKeyOptFun, 36, 52, 52},	//52		�趨Һλ��Χ����

};

void MainWindow(void)
{
	uint8_t test[6];

	GetNum(1099, 1, test);
	DisplayOneLine24x32_with_params(4, 2, 5, test);
}

void DisplayWindow(void)
{
	
	if(needRefresh == TRUE)
	{
		CleanScreen();
		needRefresh = FALSE;
		displayModel(0);
	}
}

void ReturnToMainWindowKeyOptFun(uint8_t key)
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
			ReturnBackToMainWindowEnterKeyOpt();
			break;
		default:
			break;
	}
}
void SetRefresh(bool refresh)
{
	needRefresh = refresh;
}

void StartScreenRefreshTimer(void)
{
	TmrCfgFnct(TRUE, SCREEN_REFRESH, SetRefresh, (void *)TRUE);                  /* Execute when Timer #0 times out          */
	TmrSetMST(SCREEN_REFRESH, 0, 0, 10);                                 /* Set timer #0 to 0 min., 10 sec. 0/10 sec. */
	TmrStart(SCREEN_REFRESH);
}

void StopScreenRefreshTimer(void)
{
	TmrStop(SCREEN_REFRESH);
}

void ReturnToSubMenuKeyOptFun(uint8_t key)
{
	StopScreenRefreshTimer();
	needRefresh = TRUE;
	switch(key)
	{
		case ENTER:
			displayModel = DisplayMenu;
			MoveToNextMenu();
			break;
		default:
			break;
	}
}



void KeyOptFun(uint8_t key)
{
	needRefresh = TRUE;
	if(displayModel == MainWindow)
	{
		displayModel = DisplayMenu;
	} else {
		
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
				break;
			default:
				break;
		}
	}
	
}

/* Private Fun */

void MoveToLeftMenu(void)
{
	if(currentMenu == windowPointer)
	{
		windowPointer = menus[currentMenu].left;
	}
	
	currentMenu = menus[currentMenu].left;
}

void MoveToRightMenu(void)
{
	uint8_t w1 = menus[windowPointer].right;
	uint8_t w2 = menus[w1].right;
	uint8_t w3 = menus[w2].right;
	
	uint8_t m1 = menus[currentMenu].right;
	uint8_t m2 = menus[m1].right;
	uint8_t m3 = menus[m2].right;

	if((currentMenu == w3) && (currentMenu != m3))
	{
		windowPointer = menus[windowPointer].right;
	}
	
	currentMenu = menus[currentMenu].right;
}

void ReturnBackToMainWindowEnterKeyOpt(void)
{
	currentMenu = 0;
	needRefresh = TRUE;
	displayModel = MainWindow;
	windowPointer = currentMenu;
}

void DisplayMenu(void)
{
	uint8_t i = 0, isSelected = FALSE, p = windowPointer;
	
	do {
		isSelected = (p == currentMenu) ? TRUE : FALSE;
		DisplayOneLine16x16_with_params(4, i * 2, menus[p].displayContentLength, menus[p].displayContent, isSelected);

		p = menus[p].right;
		i++;
	} while((i < MENU_WINDOW_SIZE) && (p != windowPointer));
}

void MoveToNextMenu(void)
{
	currentMenu = menus[currentMenu].next;
	windowPointer = currentMenu;
}

void ChangeDisplayMode(void * currentDisplayMode)
{
	needRefresh = TRUE;
	displayModel = currentDisplayMode;
}

