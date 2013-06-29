#include "Include.h"
#include "Menu.h"

void KeyOperatingFunction(uint8_t key);
void UpKeyOpt(void);
void DownKeyOpt(void);
void EnterKeyOpt(void);
void DisplayMenu(void);
void ShowDeviceStatusFunction(uint8_t key);

extern uint8_t windowPointer = 0, currentMenu = 0, needRefresh = TRUE;

const Menu menus[52] = {{4, "信息查询",  KeyOperatingFunction, TRUE, 0, 5, 4, 1}, 			// 0
					 {4, "人工模式",  KeyOperatingFunction, TRUE, 0, 8, 0, 2}, 					// 1 
					 {4, "参数设置",  KeyOperatingFunction, TRUE, 0, 11, 1, 3}, 				// 2 
					 {4, "系统校准",  KeyOperatingFunction, TRUE, 0, 26, 2, 4}, 				// 3
					 {2, "返回",  	 KeyOperatingFunction, TRUE, 0, 0, 3, 0}, 					// 4
					 
					 {4, "基本信息",  KeyOperatingFunction, TRUE, 0, NULL, 7, 6}, 				// 5
					 {4, "运行参数",  KeyOperatingFunction, TRUE, NULL, NULL, 5, 7}, 			// 6
					 {2, "返回",  	KeyOperatingFunction, TRUE, NULL, NULL, 6, 5}, 				// 7
					 
					 {5, "继电器控制",  KeyOperatingFunction, TRUE, NULL, NULL, 10, 9}, 		// 8
					 {4, "阀门控制",  KeyOperatingFunction, TRUE, NULL, NULL, 8, 10}, 			// 9
					 {2, "返回",  	KeyOperatingFunction, TRUE, NULL, NULL, 9, 8}, 				// 10
					 
					 {6, "输出控制模式",  KeyOperatingFunction, TRUE, NULL, NULL, 25, 12}, 	// 11
					 {4, "量程上限",  KeyOperatingFunction, TRUE, NULL, NULL, 11, 13}, 		// 12
					 {4, "量程下限",  KeyOperatingFunction, TRUE, NULL, NULL, 12, 14}, 		// 13
					 {4, "告警上限",  KeyOperatingFunction, TRUE, NULL, NULL, 13, 15}, 		// 14
					 {4, "告警下限",  KeyOperatingFunction, TRUE, NULL, NULL, 14, 16}, 		// 15
					 {5, "告警上上限",  KeyOperatingFunction, TRUE, NULL, NULL, 15, 17}, 		// 16
					 {5, "告警下下限",  KeyOperatingFunction, TRUE, NULL, NULL, 16, 18}, 		// 17
					 {4, "设定液位",  KeyOperatingFunction, TRUE, NULL, NULL, 17, 19}, 		// 18
					 {5, "阀门正反向",  KeyOperatingFunction, TRUE, NULL, NULL, 18, 20}, 		// 19
					 {4, "阻尼系数",  KeyOperatingFunction, TRUE, NULL, NULL, 19, 21}, 		// 20
					 {4, "比例增益",  KeyOperatingFunction, TRUE, NULL, NULL, 20, 22}, 		// 21
					 {4, "积分时间",  KeyOperatingFunction, TRUE, NULL, NULL, 21, 23}, 		// 22
					 {4, "微分时间",  KeyOperatingFunction, TRUE, NULL, NULL, 22, 24}, 		// 23
					 {5, "液位上下限",  KeyOperatingFunction, TRUE, NULL, NULL, 23, 25}, 		// 24
					 {2, "返回",  	KeyOperatingFunction, TRUE, NULL, NULL, 24, 11}, 			// 25
					 
					 {4, "零点校准",  KeyOperatingFunction, TRUE, NULL, NULL, 28, 27}, 		// 26
					 {4, "满度校准",  KeyOperatingFunction, TRUE, NULL, NULL, 26, 28}, 		// 27
					 {2, "返回",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 28
					 
					 {6, "输出控制模式",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 	// 29
					 {4, "量程上限",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 30
					 {4, "量程下限",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 31
					 {4, "告警上限",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 32
					 {4, "告警下限",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 33
					 {5, "告警上上限",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 34
					 {5, "告警下下限",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 35
					 {4, "设定液位",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 36
					 {5, "阀门正反向",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 37
					 {4, "阻尼系数",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 38
					 {4, "阀门开度",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 39
					 {4, "比例增益",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 40
					 {4, "积分时间",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 41
					 {4, "微分时间",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 42
					 {4, "电流输出",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 43
					 {4, "电压输入",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 44
					 {5, "24V输入",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 			// 45
					 {5, "液位上下限",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 		// 46
					 {2, "返回",	 KeyOperatingFunction, TRUE, NULL, NULL, 27, 26}, 			// 47

					 {2, "厂商",	 ShowDeviceStatusFunction, TRUE, NULL, NULL, 27, 26}, 			// 48
					 {4, "出厂日期",	 ShowDeviceStatusFunction, TRUE, NULL, NULL, 27, 26}, 			// 49
					 {4, "检验日期",	 ShowDeviceStatusFunction, TRUE, NULL, NULL, 27, 26}, 			// 50
					 {2, "返回",	 ShowDeviceStatusFunction, TRUE, NULL, NULL, 27, 26}, 			// 51
};

void MenuInit(void)
{
	
}

void DisplayWindow(void)
{
	
	if(needRefresh == TRUE)
	{
		CleanScreen();
		needRefresh = FALSE;
		DisplayMenu();
	}
}

void ShowDeviceStatusFunction(uint8_t key)
{
	needRefresh = TRUE;
	
	switch(key)
	{
		case ENTER:
			EnterKeyOpt();
			break;
		default:
			break;
	}
}

void KeyOperatingFunction(uint8_t key)
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
			EnterKeyOpt();
			break;
		default:
			break;
	}
}

/* Private function */

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

void EnterKeyOpt(void)
{
	currentMenu = menus[currentMenu].next;
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

