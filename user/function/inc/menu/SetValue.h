#define 	SET_VAL_BASE	44
#define 	ADD				0x01
#define 	MINUS			0x02

void SetValueKeyOptFun(uint8_t key);
void ChangeValueKeOptFun(uint8_t key);
void ReturnFromSetValueMenuKeyOptFun(uint8_t key);
void SaveValueKeOptFun(uint8_t key);
void UpdateSetValue(uint8_t how, uint8_t base);

extern uint16_t newSetValue;

