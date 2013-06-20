#define MENU_TIMEOUT_TIMER 	0

void displayMainMenu(uint8_t y);
void backToMainMenu(void);
void menuInit();


typedef struct Menu {
	struct Menu *pre;
	struct Menu *next;
   	char *displayContent;
	void (*optFun)(uint8_t);
} Menu;

