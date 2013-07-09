
/*  <<<<AO表>>>>
运行参数信息	
	0x0000	OCM		R/W	输出控制模式（0-AO，1-DO）
	0x0002	AM		R/W	自动/手动模式（0-自动，1-手动）
	0x0004	RH		R/W	量程上限（10m）
	0x0006	RL		R/W	量程下限（0m）
	0x0008	AH		R/W	告警上限
	0x000A	AL		R/W	告警下限
	0x000C	AHH		R/W	告警上上限
	0x000E	ALL		R/W	告警下下限
	0x0010	SV		R/W	设定液位
	0x0012	PV		R	当前液位
	0x0014	AOFR		R/W	AO输出正反向控制（0-正向，1-反向）
	0x0016	DAMP		R/W	阻尼系数，此处表示数字滤波时间常数（0～32s）
	0x0018	MV		R/W	PID输出值（阀门开度：0～100%）
	0x001A	P		R/W	比例增益
	0x001C	I		R/W	积分时间
	0x001E	D		R/W	微分时间
	0x0020	CO		R	控制器电流信号输出
	0x0022	VI		R	传感器电压信号输入
	0x0024	PWR		R	24V供电输入
	0x0026	ULT		R/W	设定液位范围（单位±%）,“如5m±20%（上下限）”
					
基本参数信息	
	0x0050		（‘西’）	R	厂商名称信息（如“西安维纳”）。长度可变，其中每个寄存器保存一个汉字（Unicode码），以0x0000作为整个名称字符串的结尾，最长可包含8个汉字。
	0x0052		（‘安’）	R	
	0x0054		（‘维’）	R	
	0x0056		（‘纳’）	R	
	0x0058		0x0000	R	
	0x005A		0x0000	R	
	0x005C		0x0000	R	
	0x005E		0x0000	R	
	0x0060		0x0000	R	
	0x0062		（‘A’）	R/W	型号信息（如“ABC-0123”）。长度可变，其中每个寄存器保存一个ASCII码（低字节），以0x0000作为整个字符串的结尾，最长可包含8个字符。
	0x0064		（‘B’）	R/W	
	0x0066		（‘C’）	R/W	
	0x0068		（‘-’）	R/W	
	0x006A		（‘0’）	R/W	
	0x006C		（‘1’）	R/W	
	0x006E		（‘2’）	R/W	
	0x0070		（‘3’）	R/W	
	0x0072		0x0000	R/W	
	0x0074		（0x2013）	R/W	出厂日期：年（BCD码）
	0x0076		（0x0616）	R/W	出厂日期：月日（BCD码）
	0x0078		（0x2013）	R/W	检验日期：年（BCD码）
	0x007A		（0x0620）	R/W	检验日期：月日（BCD码）

	<<<<DO表>>>>	
MODBUS功能码：读线圈（1）					
运行参数信息	
	0x0000	RS		R/W	继电器状态（0-闭合，1-打开）
*/


/*
typedef struct Data{
	uint16_t		OCM;	// 输出控制模式（0-AO，1-DO）
	uint16_t		AM;		// 自动/手动模式（0-自动，1-手动）
	uint16_t		RH;		// 量程上限（10m） (1000倍) 
	uint16_t		RL;		// 量程下限（0m）  (1000倍) 
	uint16_t		AH;		// 告警上限	(1000倍) 
	uint16_t		AL;		// 告警下限 (1000倍) 
	uint16_t		AHH;	// 告警上上限 (1000倍) 
	uint16_t		ALL;	// 告警下下限 (1000倍) 
	uint16_t		SV;		// 设定液位 (1000倍) 
	uint16_t		PV;		// 当前液位 (1000倍) 
	uint16_t		AOFR;	//AO输出正反向控制（0-正向，1-反向）
	uint16_t		DAMP;	//阻尼系数，此处表示数字滤波时间常数（0～32s）
	
	uint16_t		MV;		// PID输出值（阀门开度：0～100%）
	uint16_t		P;		//比例增益
	uint16_t 		I;		//积分时间
	uint16_t 		D;		//微分时间
	uint16_t 		CO;		//控制器电流信号输出
	uint16_t 		VI;		//传感器电压信号输入
	uint16_t 		PSP;	//24V供电输入
	uint16_t 		SVH;		//设定液位上限 （DO使用）
	uint16_t 		SVL;		//设定液位上限 （DO使用）
	uint16_t		VendorInfo[9];	//厂商名称信息（如“西安维纳”）
	uint16_t		ProductInfo[9];	//型号信息（如“ABC-0123”）
	
	uint16_t		ReleaseYear;	//出厂日期：年（BCD码）
	uint16_t		ReleaseDate;	//出厂日期：月日（BCD码）
	uint16_t		QualifiedYear;	//检验日期：年（BCD码）
	uint16_t		QualifiedDate;	//检验日期：月日（BCD码）	
} Data;
*/

#define		OCM_ADDR		0x0000	
#define		AM_ADDR			0x0002
#define		RH_ADDR			0x0004
#define		RL_ADDR			0x0006
#define		AH_ADDR			0x0008
#define		AL_ADDR			0x000A
#define		AHH_ADDR		0x000C
#define		ALL_ADDR		0x000E
#define		SV_ADDR			0x0010
#define		PV_ADDR			0x0012
#define		AOFR_ADDR		0x0014
#define		DAMP_ADDR		0x0016
#define		MV_ADDR			0x0018
#define		P_ADDR			0x001A
#define		I_ADDR			0x001C
#define		D_ADDR			0x001E
#define		CO_ADDR			0x0020
#define		VI_ADDR			0x0022
#define		PWR_ADDR		0x0024
#define		SVH_ADDR		0x0026
#define		SVL_ADDR		0x0028
#define		CZ_ADDR			0x002A
#define		CF_ADDR			0x002C

#define		VENDOR0_ADDR	0x0050
#define		VENDOR1_ADDR	0x0052
#define		VENDOR2_ADDR	0x0054
#define		VENDOR3_ADDR	0x0056
#define		VENDOR4_ADDR	0x0058
#define		VENDOR5_ADDR	0x005A
#define		VENDOR6_ADDR	0x005C
#define		VENDOR7_ADDR	0x005E
#define		VENDOR8_ADDR	0x0060
#define		PRODUCT0_ADDR	0x0062
#define		PRODUCT1_ADDR	0x0064
#define		PRODUCT2_ADDR	0x0066
#define		PRODUCT3_ADDR	0x0068
#define		PRODUCT4_ADDR	0x006A
#define		PRODUCT5_ADDR	0x006C
#define		PRODUCT6_ADDR	0x006E
#define		PRODUCT7_ADDR	0x0070
#define		PRODUCT8_ADDR	0x0072
#define		R_YEAR_ADDR		0x0074
#define		R_DATE_ADDR		0x0076
#define		Q_YEAR_ADDR		0x0078
#define		Q_DATE_ADDR		0x007A

#define 	OPEN			0x01
#define 	CLOSE			0x00

uint16_t GetData(uint16_t type);
void UpdateData(uint8_t type, uint16_t val);
uint16_t GetRelayStatus(void);
void SetRelay(int16_t status);

extern uint8_t Data[52];

extern uint16_t DO;

extern uint16_t deviceAddr;

typedef struct Calibration {
	uint16_t 	zero;
	uint16_t 	ref;
	uint16_t 	max;
} Calibration;

