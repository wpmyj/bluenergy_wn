#define 	AUTO		0x00
#define 	MANUAL		0x01

void SetOptMod(uint16_t optMod);
void RestoreOptMod(void);
void SaveOptMod(void);
void OperateRelay(uint16_t status);

extern uint16_t preOptMod;

