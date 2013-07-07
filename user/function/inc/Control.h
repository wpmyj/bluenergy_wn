#define 	AO_MOD		0x00
#define 	DO_MOD		0x01

#define		P 	0x00
#define		I 	0x01
#define		D 	0x02

void RegulatingValveControl(void);
uint16_t Convert_MV_To_DAC_Raw(uint16_t mv);

