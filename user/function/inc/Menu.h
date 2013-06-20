#define MENU_TIMEOUT_TIMER 	0

void displayMainMenu(uint8_t y);
void backToMainMenu(void);


typedef struct {
   	char *content;
	void (*optFun)(uint8_t);
} Menu;

