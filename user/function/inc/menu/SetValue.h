#define 	SET_VAL_BASE	51
#define 	ADD				0x01
#define 	MINUS			0x02

void SetValueKeOptFun(uint8_t key);
void ChangeValueKeOptFun(uint8_t key);
void ReturnFromSetValueMenuKeyOptFun(uint8_t key);
void SaveValueKeOptFun(uint8_t key);

extern uint16_t newSetValue;

