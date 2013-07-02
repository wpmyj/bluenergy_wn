#include "Include.h"
#include "SubMenus.h"
#include "Menu.h"

extern uint8_t windowPointer = 0, currentMenu = 0, needRefresh = TRUE;
extern void (*displayModel)(uint8_t);

extern const Menu menus[55] = {{4, "信息查询",  KeyOptFun, TRUE, 5, 4, 1}, 			// 0
					 {4, "人工模式",  KeyOptFun, TRUE, 8, 0, 2}, 				// 1 
					 {4, "参数设置",  KeyOptFun, TRUE, 11, 1, 3}, 				// 2 
					 {4, "系统校准",  KeyOptFun, TRUE, 26, 2, 4}, 				// 3
					 {2, "返回",  	 ReturnToMainWindowKeyOptFun, TRUE, 0, 3, 0}, // 4
					 
					 {4, "基本信息",  SubMenuKeyOptFun, TRUE, 48, 7, 6}, 			// 5
					 {4, "运行参数",  KeyOptFun, TRUE, 29, 5, 7}, 			// 6
					 {2, "返回",  	KeyOptFun, TRUE, 0, 6, 5}, 				// 7
					 
					 {5, "电磁阀控制",  DisplaySetRelayStatusKeOptFun, TRUE, 49, 10, 9}, 		// 8
					 {5, "调节阀控制",  KeyOptFun, TRUE, 50, 8, 10}, 			// 9
					 {2, "返回",  	KeyOptFun, TRUE, 0, 9, 8}, 				// 10
					 
					 {6, "输出控制模式",  KeyOptFun, TRUE, NULL, 25, 12}, 	// 11
					 {4, "量程上限",  KeyOptFun, TRUE, NULL, 11, 13}, 		// 12
					 {4, "量程下限",  KeyOptFun, TRUE, NULL, 12, 14}, 		// 13
					 {4, "告警上限",  KeyOptFun, TRUE, NULL, 13, 15}, 		// 14
					 {4, "告警下限",  KeyOptFun, TRUE, NULL, 14, 16}, 		// 15
					 {5, "告警上上限",  KeyOptFun, TRUE, NULL, 15, 17}, 		// 16
					 {5, "告警下下限",  KeyOptFun, TRUE, NULL, 16, 18}, 		// 17
					 {4, "设定液位",  KeyOptFun, TRUE, 51, 17, 19}, 		// 18
					 {5, "阀门正反向",  KeyOptFun, TRUE, NULL, 18, 20}, 		// 19
					 {4, "阻尼系数",  KeyOptFun, TRUE, NULL, 19, 21}, 		// 20
					 {4, "比例增益",  KeyOptFun, TRUE, NULL, 20, 22}, 		// 21
					 {4, "积分时间",  KeyOptFun, TRUE, NULL, 21, 23}, 		// 22
					 {4, "微分时间",  KeyOptFun, TRUE, NULL, 22, 24}, 		// 23
					 {5, "液位上下限",  KeyOptFun, TRUE, NULL, 23, 25}, 		// 24
					 {2, "返回",  	KeyOptFun, TRUE, NULL, 24, 11}, 			// 25
					 
					 {4, "零点校准",  KeyOptFun, TRUE, NULL, 28, 27}, 		// 26
					 {4, "满度校准",  KeyOptFun, TRUE, NULL, 26, 28}, 		// 27
					 {2, "返回",	 KeyOptFun, TRUE, NULL, 27, 26}, 		// 28
					 
					 {6, "输出控制模式",	 KeyOptFun, TRUE, NULL, 47, 30}, 	// 29
					 {4, "量程上限",	 KeyOptFun, TRUE, NULL, 29, 31}, 		// 30
					 {4, "量程下限",	 KeyOptFun, TRUE, NULL, 30, 32}, 		// 31
					 {4, "告警上限",	 KeyOptFun, TRUE, NULL, 31, 33}, 		// 32
					 {4, "告警下限",	 KeyOptFun, TRUE, NULL, 32, 34}, 		// 33
					 {5, "告警上上限",	 KeyOptFun, TRUE, NULL, 33, 35}, 		// 34
					 {5, "告警下下限",	 KeyOptFun, TRUE, NULL, 34, 36}, 		// 35
					 {4, "设定液位",	 DisplaySetValeKeOptFun, TRUE, 51, 35, 37}, 		// 36
					 {5, "阀门正反向",	 KeyOptFun, TRUE, NULL, 36, 38}, 		// 37
					 {4, "阻尼系数",	 KeyOptFun, TRUE, NULL, 37, 39}, 		// 38
					 {4, "阀门开度",	 KeyOptFun, TRUE, NULL, 38, 40}, 		// 39
					 {4, "比例增益",	 KeyOptFun, TRUE, NULL, 39, 41}, 		// 40
					 {4, "积分时间",	 KeyOptFun, TRUE, NULL, 40, 42}, 		// 41
					 {4, "微分时间",	 KeyOptFun, TRUE, NULL, 41, 43}, 		// 42
					 {4, "电流输出",	 KeyOptFun, TRUE, NULL, 42, 44}, 		// 43
					 {4, "电压输入",	 KeyOptFun, TRUE, NULL, 43, 45}, 		// 44
					 {5, "24V输入",	 KeyOptFun, TRUE, NULL, 	   44, 46}, 		// 45
					 {5, "液位上下限",	 KeyOptFun, TRUE, NULL, 45, 47}, 		// 46
					 {2, "返回",	 KeyOptFun, TRUE, NULL,     46, 29}, 		// 47
			
					 {0, "",	 ReturnToSubMenuKeyOptFun, TRUE, 5, 48, 48}, 			// 48  	出厂信息

					 {2, "返回",  SetRelayKeOptFun, TRUE, 8, 49, 49}, 			// 49 	继电器控制
					 
					 {0, "",	 ReturnToSubMenuKeyOptFun, TRUE, 9, 50, 50}, 			// 50	阀门控制

				   	 {0, "",	 ReturnToSubMenuKeyOptFun, TRUE, 29, 51, 51} 			// 51	运行参数 - 设定液位查询
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
			UpKeyOpt();
			break;
		case DOWN:
			DownKeyOpt();
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
				UpKeyOpt();
				break;
			case DOWN:
				DownKeyOpt();
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

void UpKeyOpt(void)
{
	if(currentMenu == windowPointer)
	{
		windowPointer = menus[currentMenu].left;
	}
	
	currentMenu = menus[currentMenu].left;
}

void DownKeyOpt(void)
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

