#include "Include.h"
#include "SubMenus.h"
#include "Menu.h"
#include "Actuator.h"

extern uint8_t windowPointer = 0, currentMenu = 0, needRefresh = TRUE;
extern void (*displayModel)(uint8_t);

extern const Menu menus[72] = {{4, "信息查询",  KeyOptFun, 5, 4, 1}, 	// 0
					 {4, "人工模式",  KeyOptFun, 8, 0, 2}, 				// 1 
					 {4, "参数设置",  KeyOptFun, 11, 1, 3}, 				// 2 
					 {4, "系统校准",  KeyOptFun, 26, 2, 4}, 				// 3
					 {2, "返回",  	 ReturnToMainWindowKeyOptFun, 0, 3, 0}, // 4
					 
					 {4, "基本信息",  SubMenuKeyOptFun, 41, 7, 6}, 		// 5
					 {4, "运行参数",  KeyOptFun, 29, 5, 7}, 			// 6
					 {2, "返回",  	KeyOptFun, 0, 6, 5}, 				// 7
					 
					 {5, "电磁阀控制",  DisplayRelayStatusControlKeyOptFun, 42, 10, 9}, // 8
					 {5, "调节阀控制",  DisplayValveControlKeyOptFun, 67, 8, 10}, 			// 9
					 {2, "返回",  	KeyOptFun,0, 9, 8}, 				// 10
					 
					 {6, "输出控制模式",  KeyOptFun, NULL, 25, 12}, 	// 11
					 {4, "量程上限",  KeyOptFun, NULL, 11, 13}, 		// 12
					 {4, "量程下限",  KeyOptFun, NULL, 12, 14}, 		// 13
					 {4, "告警上限",  KeyOptFun, NULL, 13, 15}, 		// 14
					 {4, "告警下限",  KeyOptFun, NULL, 14, 16}, 		// 15
					 {5, "告警上上限",  KeyOptFun, NULL, 15, 17}, 		// 16
					 {5, "告警下下限",  KeyOptFun, NULL, 16, 18}, 		// 17
					 {4, "设定液位",  SetValueKeyOptFun, 44, 17, 19}, 	// 18
					 {5, "阀门正反向",  KeyOptFun, NULL, 18, 20}, 		// 19
					 {4, "阻尼系数",  KeyOptFun, NULL, 19, 21}, 		// 20
					 {4, "比例增益",  KeyOptFun, NULL, 20, 22}, 		// 21
					 {4, "积分时间",  KeyOptFun, NULL, 21, 23}, 		// 22
					 {4, "微分时间",  KeyOptFun, NULL, 22, 24}, 		// 23
					 {5, "液位上下限",  KeyOptFun, NULL, 23, 62}, 		// 24
					 {2, "返回",  	KeyOptFun, NULL, 62, 11}, 			// 25
					 
					 {4, "零点校准",  KeyOptFun, NULL, 28, 27}, 		// 26
					 {4, "满度校准",  KeyOptFun, NULL, 26, 28}, 		// 27
					 {2, "返回",	 KeyOptFun, NULL, 27, 26}, 			// 28
					 
					 {6, "输出控制模式",	 DisplayOutputControlModInfoKeyOptFun, 55, 40, 30}, 	// 29
					 {4, "量程范围",	 DisplayMeasureRangeKeyOptFun, 53, 29, 31}, 		// 30
					 {4, "告警范围",	 DisplayAlarmRangeKeyOptFun, 54, 30, 32}, 		// 31		
					 {4, "设定液位",	 DisplaySetValeKeyOptFun, 50, 31, 33}, // 32
					 {4, "阀门状态",	 DisplayRelayStatusInfoKeyOptFun, 56, 32, 34}, 		// 33
					 {4, "阻尼系数",	 DisplayDampInfoKeyOptFun, 57, 33, 35}, 		// 34		
					 {5, "皮挨帝系数",	 DisplayPID_InfoKeyOptFun, 58, 34, 36}, 			// 35		
					 {4, "电流输出",	 DisplayCurrentOutputKeyOptFun, 51, 35, 37}, 	// 36
					 {4, "电压输入",	 DisplayVolageInputInfoKeyOptFun, 59, 36, 38}, 		// 37
					 {4, "电源电压",	 KeyOptFun, NULL, 37, 39}, 		// 38
					 {6, "液位设定范围", DisplaySetValueRangeKeyOptFun, 52, 38, 60}, 	// 39
					 {2, "返回",	 KeyOptFun, NULL,     60, 29}, 		// 40
			
					 {0, "",	 ReturnToSubMenuKeyOptFun, 5, 41, 41}, 	// 41  	出厂信息

					 {2, "返回",  SetRelayKeyOptFun, 8, 42, 42}, 			// 42 	继电器控制
					 
					 {0, "",	 ReturnToSubMenuKeyOptFun, 9, 43, 43}, 	// 43	阀门控制

					  // 运行参数 - 设定液位查询

				   	 {1, "",	 ChangeValueKeyOptFun, 18, 47, 45},	//44		液位整数1 位

					 {1, "",	 ChangeValueKeyOptFun, 18, 44, 46},	//45		液位小数1 位

					 {1, "",	 ChangeValueKeyOptFun, 18, 45, 47},	//46		液位小数2 位

					 {1, "",	 ChangeValueKeyOptFun, 18, 46, 48},	//47		液位小数3 位

					 {2, "保存",	 SaveValueKeyOptFun, 18, 47, 49},	//48		液位保存

					 {2, "返回",	 ReturnFromSetValueMenuKeyOptFun, 18, 48, 44}, //49		液位返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 32, 50, 50},	//50		液位返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 36, 51, 51},	//51		电流输出返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 39, 52, 52},	//52		设定液位范围返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 30, 53, 53},	//53		量程范围返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 31, 54, 54},	//54		告警范围返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 29, 55, 55},	//55		 输出模式返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 33, 56, 56},	//56		 输出模式返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 34, 57, 57},	//57		 阻尼系数返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 35, 58, 58},	//58		PID系数返回
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 37, 59, 59},	//59		PID系数返回
					 {4, "设备地址", DisplayDeviceAddrKeyOptFun, 61, 39, 40}, 	// 60
					 {2, "返回",	 ReturnToSubMenuKeyOptFun, 60, 61, 61},	//61	PID系数返回

					 {4, "设备地址", SetDeviceAddrKeyOptFun, 63, 24, 25}, // 62
					 {1, "",	 ChangeDeviceAddrKeyOptFun, 64, 66, 64},	//63		液位小数2 位
					 {1, "",	 ChangeDeviceAddrKeyOptFun, 65, 63, 65},	//64		液位小数3 位
					 {2, "保存",	 SaveDeviceAddrKeyOptFun, 63, 63, 66},	//65		液位保存
					 {2, "返回",	 ReturnFromSetValueMenuKeyOptFun, 62, 65, 63}, //66		液位返回

					 {1, "",	 ChangeValveValueKeyOptFun, 68, 70, 68},	//67		液位小数2 位
					 {1, "",	 ChangeValveValueKeyOptFun, 69, 67, 69},	//68		液位小数3 位
					 {1, "",	 ChangeValveValueKeyOptFun, 70, 68, 70},	//69		液位小数3 位
					 {2, "保存",	 SaveValveValueKeyOptFun, 67, 67, 71},	//70	液位保存
					 {2, "返回",	 ReturnFromSetValueMenuKeyOptFun, 9, 70, 67}, //71		液位返回

};

void MainWindow(void)
{
	uint8_t currentValue[4];
	//sprintf(currentValue, "%4.3f", ((float)GetData(PV_ADDR)) / 1000);
	currentValue[0] = (GetData(PV_ADDR) / 1000) % 10;
	currentValue[1] = (GetData(PV_ADDR) / 100) % 10;
	currentValue[2] = (GetData(PV_ADDR) / 10) % 10;
	currentValue[3] = (GetData(PV_ADDR)) % 10;
	
	DisplayOne24x32(4, 2,  currentValue[0] + 48, FALSE);
	DisplayOneGB12x16(28, 4, 0, FALSE);
	DisplayOne24x32(40, 2, currentValue[1] + 48, FALSE);
	DisplayOne24x32(64, 2, currentValue[2] + 48, FALSE);
	DisplayOne24x32(88, 2, currentValue[3] + 48, FALSE);
	DisplayOneGB12x16(115, 4, 3, FALSE); // m
	if(GetData(OCM_ADDR) == 0)
	{
		DisplayOneGB12x16(115, 2, 2, FALSE); // S 
	}
	else
	{
		DisplayOneGB12x16(115, 2, 1, FALSE); // R
	}
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
			TmrStart(MAIN_WINDOW_REFRESH_TIMER);
			TmrStop(MENU_TIMEOUT_TIMER);
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
		TmrStop(MAIN_WINDOW_REFRESH_TIMER);
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

void MenuInit(void)
{
	displayModel = MainWindow;
}

void MainWindowRefreshTimer(void)
{
	needRefresh = TRUE;
}

void MainWindowRefreshTimerInit(void)
{
	TmrCfg(MAIN_WINDOW_REFRESH_TIMER, MainWindowRefreshTimer, (void *)0, 0, 1, 0, TRUE, TRUE);
}

void MenuTimeout(void)
{
	needRefresh = TRUE;
	displayModel = MainWindow;
	currentMenu = windowPointer = 0;
	RestoreOptMod();
	StartScreenRefreshTimer();
}

void MenuTimeoutTimerInit(void)
{
	TmrCfg(MENU_TIMEOUT_TIMER, MenuTimeout, (void *)0, 0, 20, 0, FALSE, TRUE);
}

