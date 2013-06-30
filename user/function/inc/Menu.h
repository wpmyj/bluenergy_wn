#define MENU_TIMEOUT_TIMER 	0
#define MENU_WINDOW_SIZE	4

#define UP					0
#define	DOWN				1
#define	ENTER				2

typedef struct Menu {	
	uint8_t displayContentLength;
   	char *displayContent;		
	void (*optFun)(uint8_t);
	uint8_t refresh;
	uint8_t next;
	uint8_t left;
	uint8_t right;
} Menu;

void DisplayWindow(void);
void MainWindow(void);

