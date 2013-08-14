#define 	DATA_SIZE		164

#define		OCM_ADDR		0	
#define		AM_ADDR			1
#define		RH_ADDR			2
#define		RL_ADDR			3
#define		AH_ADDR			4
#define		AL_ADDR			5
#define		AHH_ADDR		6
#define		ALL_ADDR		7
#define		SV_ADDR			8
#define		PV_ADDR			9

#define		AOFR_ADDR		20
#define		DAMP_ADDR		21
#define		MV_ADDR			22
#define		P_ADDR			23
#define		I_ADDR			24
#define		D_ADDR			25
#define		CO_ADDR			26
#define		VI_ADDR			27
#define		PWR_ADDR		28
#define		SVH_ADDR		29
#define		SVL_ADDR		30
#define		RS_ADDR			31
#define		DA_ADDR			32
#define		MH_ADDR			33
#define		ZR_ADDR			34
#define		RR_ADDR			35
#define		RE_ADDR			36
#define		ST_ADDR			37
#define		DV_ADDR			38
#define		EC_ADDR			39
#define		MT_ADDR			40

#define		VENDOR0_ADDR	60
#define		VENDOR1_ADDR	61
#define		VENDOR2_ADDR	62
#define		VENDOR3_ADDR	63
#define		VENDOR4_ADDR	64
#define		VENDOR5_ADDR	65
#define		VENDOR6_ADDR	66
#define		VENDOR7_ADDR	67
#define		VENDOR8_ADDR	68
#define		PRODUCT0_ADDR	69
#define		PRODUCT1_ADDR	70
#define		PRODUCT2_ADDR	71
#define		PRODUCT3_ADDR	72
#define		PRODUCT4_ADDR	73
#define		PRODUCT5_ADDR	74
#define		PRODUCT6_ADDR	75
#define		PRODUCT7_ADDR	76
#define		PRODUCT8_ADDR	77
#define		R_YEAR_ADDR		78
#define		R_DATE_ADDR		79
#define		Q_YEAR_ADDR		80
#define		Q_DATE_ADDR		81

#define 	OPEN			0x01
#define 	CLOSE			0x00

#define 	FLASH_DATA_ADDR			0x08019000
#define		FLASH_OPT_FLAG_ADDR		0x08019800	

uint16_t GetData(uint16_t type);
void UpdateData(uint8_t type, uint16_t val, bool writeToFlash);
uint16_t GetRelayStatus(void);
void SetRelay(int16_t status);

extern uint8_t Data[DATA_SIZE];

