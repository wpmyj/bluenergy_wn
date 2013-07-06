#define MENU_WINDOW_SIZE	4

#define UP					0
#define	DOWN				1
#define	ENTER				2


void DisplayWindow(void);
void MainWindow(void);
void MoveToLeftMenu(void);
void MoveToRightMenu(void);
void KeyOptFun(uint8_t key);
void DisplayMenu(void);
void ReturnToSubMenuKeyOptFun(uint8_t key);
void ReturnToMainWindowKeyOptFun(uint8_t key);
void ReturnBackToMainWindowEnterKeyOpt(void);
void SubMenuEnterKeyOpt(void);
void SetRefresh(bool refresh);
void StartScreenRefreshTimer(void);
void StopScreenRefreshTimer(void);
void MoveToNextMenu(void);
void ChangeDisplayMode(void * currentDisplayMode);
void MainWindowRefreshTimerInit(void);

typedef struct Menu {	
	uint8_t displayContentLength;
   	char *displayContent;		
	void (*optFun)(uint8_t);
	uint8_t next;
	uint8_t left;
	uint8_t right;
} Menu;

