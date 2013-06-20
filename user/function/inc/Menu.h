#define MENU_TIMEOUT_TIMER 	0
#define MENU_WINDOW_SIZE	4

void displayMainMenu(void);
void backToMainMenu(void);
void menuInit();


typedef struct Menu {
	struct Menu *pre;
	struct Menu *next;
	bool refresh;
	uint8_t position;
	uint8_t displayContentLength;
   	char *displayContent;		
	void (*optFun)(uint8_t);	
} Menu;

