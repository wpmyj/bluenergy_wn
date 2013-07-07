#define 	AUTO		0x00
#define 	MANUAL		0x01

void SetOptMod(uint16_t optMod, uint16_t outputMod);
void RestoreOptMod(void);
void SaveOptMod(void);
void OperateRelay(uint16_t status);
void OperateValve(uint16_t val);

extern uint16_t preOptMod, preOutputMod;

