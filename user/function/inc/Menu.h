#define MENU_TIMEOUT_TIMER 	0
#define MENU_WINDOW_SIZE	4

void DisplayMainMenu(void);
void BackToMainMenu(void);
void MenuInit(void);


typedef struct Menu {
	uint8_t position;	
	uint8_t displayContentLength;
   	char *displayContent;		
	void (*optFun)(uint8_t);
	uint8_t menuItemsNum;
	uint8_t refresh;
	struct Menu *pre;
	struct Menu *next;
	struct Menu *left;
	struct Menu *right;
} Menu;

