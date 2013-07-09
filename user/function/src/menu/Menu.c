#include "Include.h"
#include "SubMenus.h"
#include "Menu.h"
#include "Actuator.h"

extern uint8_t windowPointer = 0, currentMenu = 0, needRefresh = TRUE;
extern void (*displayModel)(uint8_t);

extern const Menu menus[147] = {{4, "��Ϣ��ѯ",  KeyOptFun, 5, 4, 1}, 	// 0
					 {4, "�˹�ģʽ",  KeyOptFun, 8, 0, 2}, 				// 1 
					 {4, "��������",  KeyOptFun, 11, 1, 3}, 				// 2 
					 {4, "ϵͳУ׼",  KeyOptFun, 26, 2, 4}, 				// 3
					 {2, "����",  	 ReturnToMainWindowKeyOptFun, 0, 3, 0}, // 4
					 
					 {4, "������Ϣ",  SubMenuKeyOptFun, 41, 7, 6}, 		// 5
					 {4, "���в���",  KeyOptFun, 29, 5, 7}, 			// 6
					 {2, "����",  	KeyOptFun, 0, 6, 5}, 				// 7
					 
					 {5, "��ŷ�����",  DisplayRelayStatusControlKeyOptFun, 42, 10, 9}, // 8
					 {5, "���ڷ�����",  DisplayValveControlKeyOptFun, 67, 8, 10}, 			// 9
					 {2, "����",  	KeyOptFun,0, 9, 8}, 				// 10
					 
					 {6, "�������ģʽ", SetOutputModeKeyOptFun, 72, 25, 12}, 			// 11
					 {4, "��������",  SetRangeHighKeyOptFun, 74, 11, 13}, 			// 12
					 {4, "��������",  SetRangeLowKeyOptFun, 80, 12, 14}, 		// 13
					 {4, "�澯����",  SetAlarmRangeHighKeyOptFun, 86, 13, 15}, 		// 14
					 {4, "�澯����",  SetAlarmRangeLowKeyOptFun, 98, 14, 16}, 		// 15
					 {5, "�澯������",  SetAlarmRangeHighHighKeyOptFun, 92, 15, 17}, 		// 16
					 {5, "�澯������",  SetAlarmRangeLowLowKeyOptFun, 104, 16, 18}, 		// 17
					 {4, "�趨Һλ",  SetValueKeyOptFun, 44, 17, 19}, 	// 18
					 {5, "����������",  SetValveDirectionKeyOptFun, 73, 18, 20}, 		// 19
					 {4, "����ϵ��",  SetDampValueKeyOptFun, 123, 19, 21}, 			// 20
					 {4, "��������",  SetPKeyOptFun, 127, 20, 22}, 		// 21
					 {4, "����ʱ��",  SetIKeyOptFun, 132, 21, 23}, 		// 22
					 {4, "΢��ʱ��",  SetDKeyOptFun, 137, 22, 24}, 		// 23
					 {4, "Һλ����",  SetDOValueRangeHighKeyOptFun, 110, 23, 116}, 			// 24
					 {2, "����",  	KeyOptFun, 2, 62, 11}, 			// 25
					 
					 {4, "���У׼",  DisplayCalibrationZeroKeyOptFun, 142, 28, 27}, 		// 26
					 {4, "����У׼",  DisplayCalibrationFullKeyOptFun, 144, 26, 28}, 		// 27
					 {2, "����",	 KeyOptFun, 3, 27, 26}, 			// 28
					 
					 {6, "�������ģʽ",	 DisplayOutputControlModInfoKeyOptFun, 55, 40, 30}, 	// 29
					 {4, "���̷�Χ",	 DisplayMeasureRangeKeyOptFun, 53, 29, 31}, 		// 30
					 {4, "�澯��Χ",	 DisplayAlarmRangeKeyOptFun, 54, 30, 32}, 		// 31		
					 {4, "�趨Һλ",	 DisplaySetValeKeyOptFun, 50, 31, 33}, // 32
					 {4, "����״̬",	 DisplayRelayStatusInfoKeyOptFun, 56, 32, 34}, 		// 33
					 {4, "����ϵ��",	 DisplayDampInfoKeyOptFun, 57, 33, 35}, 		// 34		
					 {5, "Ƥ����ϵ��",	 DisplayPID_InfoKeyOptFun, 58, 34, 36}, 			// 35		
					 {4, "�������",	 DisplayCurrentOutputKeyOptFun, 51, 35, 37}, 	// 36
					 {4, "��ѹ����",	 DisplayVolageInputInfoKeyOptFun, 59, 36, 38}, 		// 37
					 {4, "��Դ��ѹ",	 DisplayPowerVolageInfoKeyOptFun, 146, 37, 39}, 		// 38
					 {6, "Һλ�趨��Χ", DisplaySetValueRangeKeyOptFun, 52, 38, 60}, 	// 39
					 {2, "����",	 KeyOptFun, 6,     60, 29}, 		// 40
			
					 {0, "",	 ReturnToSubMenuKeyOptFun, 5, 41, 41}, 	// 41  	������Ϣ

					 {2, "����",  SetRelayKeyOptFun, 8, 42, 42}, 			// 42 	�̵�������
					 
					 {0, "",	 ReturnToSubMenuKeyOptFun, 9, 43, 43}, 	// 43	���ſ���

					  // ���в��� - �趨Һλ��ѯ

				   	 {1, "",	 ChangeValueKeyOptFun, 18, 47, 45},	//44		Һλ����1 λ

					 {1, "",	 ChangeValueKeyOptFun, 18, 44, 46},	//45		ҺλС��1 λ

					 {1, "",	 ChangeValueKeyOptFun, 18, 45, 47},	//46		ҺλС��2 λ

					 {1, "",	 ChangeValueKeyOptFun, 18, 46, 48},	//47		ҺλС��3 λ

					 {2, "����",	 SaveValueKeyOptFun, 18, 47, 49},	//48		Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 18, 48, 44}, //49		Һλ����
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 32, 50, 50},	//50		Һλ����
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 36, 51, 51},	//51		�����������
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 39, 52, 52},	//52		�趨Һλ��Χ����
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 30, 53, 53},	//53		���̷�Χ����
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 31, 54, 54},	//54		�澯��Χ����
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 29, 55, 55},	//55		 ���ģʽ����
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 33, 56, 56},	//56		 ���ģʽ����
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 34, 57, 57},	//57		 ����ϵ������
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 35, 58, 58},	//58		PIDϵ������
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 37, 59, 59},	//59		PIDϵ������
					 {4, "�豸��ַ", DisplayDeviceAddrKeyOptFun, 61, 39, 40}, 	// 60
					 {2, "����",	 ReturnToSubMenuKeyOptFun, 60, 61, 61},	//61	PIDϵ������

					 {4, "�豸��ַ", SetDeviceAddrKeyOptFun, 63, 116, 25}, // 62
					 {1, "",	 ChangeDeviceAddrKeyOptFun, 64, 66, 64},	//63		ҺλС��2 λ
					 {1, "",	 ChangeDeviceAddrKeyOptFun, 65, 63, 65},	//64		ҺλС��3 λ
					 {2, "����",	 SaveDeviceAddrKeyOptFun, 63, 63, 66},	//65		Һλ����
					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 62, 65, 63}, //66		Һλ����

					 {1, "",	 ChangeValveValueKeyOptFun, 68, 70, 68},	//67		ҺλС��2 λ
					 {1, "",	 ChangeValveValueKeyOptFun, 69, 67, 69},	//68		ҺλС��3 λ
					 {1, "",	 ChangeValveValueKeyOptFun, 70, 68, 70},	//69		ҺλС��3 λ
					 {2, "����",	 SaveValveValueKeyOptFun, 67, 67, 71},	//70	Һλ����
					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 9, 70, 67}, //71		Һλ����

					 {2, "����",  	ChangeOutputModeKeyOptFun, 11, 72, 72}, 	  // 72

					 {2, "����",  	ChangeValveDirectionKeyOptFun, 19, 73, 73}, 	  // 73

					
					 // ���в��� - �趨���� H
				     {1, "",	   ChangeRangeHighkeyOptFun, 12, 77, 75}, //74		  Һλ����1 λ

				     {1, "",	   ChangeRangeHighkeyOptFun, 12, 74, 76}, //75		  ҺλС��1 λ

				     {1, "",	   ChangeRangeHighkeyOptFun, 12, 75, 77}, //76		  ҺλС��2 λ

				     {1, "",	   ChangeRangeHighkeyOptFun, 12, 76, 78}, //77		  ҺλС��3 λ

				     {2, "����",	   SaveRangeHighKeyOptFun, 12, 74, 79},   //78		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 12, 78, 74}, //79		Һλ����

					 // ���в��� - �趨���� L
				     {1, "",	   ChangeRangeLowkeyOptFun, 13, 83, 81}, //80		  Һλ����1 λ

				     {1, "",	   ChangeRangeLowkeyOptFun, 13, 80, 82}, //81		  ҺλС��1 λ

				     {1, "",	   ChangeRangeLowkeyOptFun, 13, 81, 83}, //82		  ҺλС��2 λ

				     {1, "",	   ChangeRangeLowkeyOptFun, 13, 82, 84}, //83		  ҺλС��3 λ

				     {2, "����",	   SaveRangeLowKeyOptFun, 13, 80, 85},   //84		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 13, 84, 80}, //85		Һλ����

					  // ���в��� - �趨�澯���� H
				     {1, "",	   ChangeAlarmRangeHighkeyOptFun, 14, 89, 87}, //86		  Һλ����1 λ

				     {1, "",	   ChangeAlarmRangeHighkeyOptFun, 14, 86, 88}, //87		  ҺλС��1 λ

				     {1, "",	   ChangeAlarmRangeHighkeyOptFun, 14, 87, 89}, //88		  ҺλС��2 λ

				     {1, "",	   ChangeAlarmRangeHighkeyOptFun, 14, 88, 90}, //89		  ҺλС��3 λ

				     {2, "����",	   SaveAlarmRangeHighKeyOptFun, 14, 86, 91},   //90		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 14, 90, 86}, //91		Һλ����

					  // ���в��� - �趨�澯���� HH
				     {1, "",	   ChangeAlarmRangeHighHighkeyOptFun, 16, 95, 93}, //92		  Һλ����1 λ

				     {1, "",	   ChangeAlarmRangeHighHighkeyOptFun, 16, 92, 94}, //93		  ҺλС��1 λ

				     {1, "",	   ChangeAlarmRangeHighHighkeyOptFun, 16, 93, 95}, //94		  ҺλС��2 λ

				     {1, "",	   ChangeAlarmRangeHighHighkeyOptFun, 16, 94, 96}, //95		  ҺλС��3 λ

				     {2, "����",	   SaveAlarmRangeHighHighKeyOptFun, 16, 92, 97},//96		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 16, 96, 92}, //97		Һλ����

					  // ���в��� - �趨�澯���� L
				     {1, "",	   ChangeAlarmRangeLowkeyOptFun, 15, 101, 99}, //98		  Һλ����1 λ

				     {1, "",	   ChangeAlarmRangeLowkeyOptFun, 15, 98, 100}, //99		  ҺλС��1 λ

				     {1, "",	   ChangeAlarmRangeLowkeyOptFun, 15, 99, 101}, //100		  ҺλС��2 λ

				     {1, "",	   ChangeAlarmRangeLowkeyOptFun, 15, 100, 102}, //101		  ҺλС��3 λ

				     {2, "����",	   SaveAlarmRangeLowKeyOptFun, 15, 98, 103},   //102		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 15, 102, 98}, //103		Һλ����

					  // ���в��� - �趨�澯���� LL
				     {1, "",	   ChangeAlarmRangeLowLowkeyOptFun, 17, 107, 105}, //104		  Һλ����1 λ

				     {1, "",	   ChangeAlarmRangeLowLowkeyOptFun, 17, 104, 106}, //105		  ҺλС��1 λ

				     {1, "",	   ChangeAlarmRangeLowLowkeyOptFun, 17, 105, 107}, //106		  ҺλС��2 λ

				     {1, "",	   ChangeAlarmRangeLowLowkeyOptFun, 17, 106, 108}, //107		  ҺλС��3 λ

				     {2, "����",	   SaveAlarmRangeLowLowKeyOptFun, 17, 104, 109},   //108		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 17, 108, 104}, //109		Һλ����

				       // ���в��� - �趨Һλ��ΧH - DO 
				     {1, "",	   ChangeDOValueRangeHighkeyOptFun, 24, 113, 111}, //110		  Һλ����1 λ

				     {1, "",	   ChangeDOValueRangeHighkeyOptFun, 24, 110, 112}, //111		  ҺλС��1 λ

				     {1, "",	   ChangeDOValueRangeHighkeyOptFun, 24, 111, 113}, //112		  ҺλС��2 λ

				     {1, "",	   ChangeDOValueRangeHighkeyOptFun, 24, 112, 114}, //113		  ҺλС��3 λ

				     {2, "����",	   SaveDOValueRangeHighKeyOptFun, 24, 110, 115},   //114		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 24, 114, 110}, //115		Һλ����

     			 	  // ���в��� - �趨�澯���� H
					 {4, "Һλ����",  SetDOValueRangeLowKeyOptFun, 117, 24, 62}, 			// 116
				
				     {1, "",	   ChangeDOValueRangeLowkeyOptFun, 14, 120, 118}, //117		  Һλ����1 λ

				     {1, "",	   ChangeDOValueRangeLowkeyOptFun, 14, 117, 119}, //118		  ҺλС��1 λ

				     {1, "",	   ChangeDOValueRangeLowkeyOptFun, 14, 118, 120}, //119		  ҺλС��2 λ

				     {1, "",	   ChangeDOValueRangeLowkeyOptFun, 14, 119, 121}, //120		  ҺλС��3 λ

				     {2, "����",	   SaveDOValueRangeLowKeyOptFun, 14, 117, 122},   //121		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 116, 121, 117}, //122		Һλ����

					   // ���в��� - �趨����ϵ��

				     {1, "",	   ChangeDampValuekeyOptFun, 20, 124, 124}, //123		  ҺλС��2 λ

				     {1, "",	   ChangeDampValuekeyOptFun, 20, 125, 125}, //124		  ҺλС��3 λ

				     {2, "����",	   SaveDampValueKeyOptFun, 20, 123, 126},  //125		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 20, 125, 123}, //126		Һλ����

					  // ���в��� - �趨P ϵ��

				     {1, "",	   ChangePkeyOptFun, 21, 129, 128}, //127		  ҺλС��2 λ

				     {1, "",	   ChangePkeyOptFun, 21, 127, 129}, //128		  ҺλС��3 λ

					 {1, "",	   ChangePkeyOptFun, 21, 128, 130}, //129		  ҺλС��3 λ

				     {2, "����",	   SavePKeyOptFun, 21, 127, 131},  //130		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 21, 130, 127}, //131		Һλ����

					  // ���в��� - �趨I ϵ��

				     {1, "",	   ChangeIkeyOptFun, 22, 134, 133}, //132		  ҺλС��2 λ

				     {1, "",	   ChangeIkeyOptFun, 22, 132, 134}, //133		  ҺλС��3 λ

					 {1, "",	   ChangeIkeyOptFun, 22, 133, 135}, //134		  ҺλС��3 λ

				     {2, "����",	   SaveIKeyOptFun, 22, 132, 136},  //135		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 22, 135, 132}, //136		Һλ����

				      // ���в��� - �趨D ϵ��

				     {1, "",	   ChangeDkeyOptFun, 23, 139, 138}, //137		  ҺλС��2 λ

				     {1, "",	   ChangeDkeyOptFun, 23, 137, 139}, //138		  ҺλС��3 λ

					 {1, "",	   ChangeDkeyOptFun, 23, 138, 140}, //139		  ҺλС��3 λ

				     {2, "����",	   SaveDKeyOptFun, 23, 137, 141},  //140		  Һλ����

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 23, 140, 137}, //141		Һλ����
						
					  // ���У׼
					 {2, "����",	   SaveCalibrationZeroKeyOptFun, 26, 142, 143},  //142		 

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 26, 142, 143}, //143		

					  // ����У׼
					 {2, "����",	   SaveCalibrationFullKeyOptFun, 27, 144, 145},  //144	

					 {2, "����",	 ReturnFromSetValueMenuKeyOptFun, 27, 144, 145}, //145	

					 {2, "����",	 ReturnToSubMenuKeyOptFun, 38, 146, 146},	//146		PIDϵ������

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

