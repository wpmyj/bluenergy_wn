
/*  <<<<AO��>>>>
���в�����Ϣ	
	0x0000	OCM		R/W	�������ģʽ��0-AO��1-DO��
	0x0002	AM		R/W	�Զ�/�ֶ�ģʽ��0-�Զ���1-�ֶ���
	0x0004	RH		R/W	�������ޣ�10m��
	0x0006	RL		R/W	�������ޣ�0m��
	0x0008	AH		R/W	�澯����
	0x000A	AL		R/W	�澯����
	0x000C	AHH		R/W	�澯������
	0x000E	ALL		R/W	�澯������
	0x0010	SV		R/W	�趨Һλ
	0x0012	PV		R	��ǰҺλ
	0x0014	AOFR		R/W	AO�����������ƣ�0-����1-����
	0x0016	DAMP		R/W	����ϵ�����˴���ʾ�����˲�ʱ�䳣����0��32s��
	0x0018	MV		R/W	PID���ֵ�����ſ��ȣ�0��100%��
	0x001A	P		R/W	��������
	0x001C	I		R/W	����ʱ��
	0x001E	D		R/W	΢��ʱ��
	0x0020	CO		R	�����������ź����
	0x0022	VI		R	��������ѹ�ź�����
	0x0024	PWR		R	24V��������
	0x0026	ULT		R/W	�趨Һλ��Χ����λ��%��,����5m��20%�������ޣ���
					
����������Ϣ	
	0x0050		����������	R	����������Ϣ���硰����ά�ɡ��������ȿɱ䣬����ÿ���Ĵ�������һ�����֣�Unicode�룩����0x0000��Ϊ���������ַ����Ľ�β����ɰ���8�����֡�
	0x0052		����������	R	
	0x0054		����ά����	R	
	0x0056		�����ɡ���	R	
	0x0058		0x0000	R	
	0x005A		0x0000	R	
	0x005C		0x0000	R	
	0x005E		0x0000	R	
	0x0060		0x0000	R	
	0x0062		����A����	R/W	�ͺ���Ϣ���硰ABC-0123���������ȿɱ䣬����ÿ���Ĵ�������һ��ASCII�루���ֽڣ�����0x0000��Ϊ�����ַ����Ľ�β����ɰ���8���ַ���
	0x0064		����B����	R/W	
	0x0066		����C����	R/W	
	0x0068		����-����	R/W	
	0x006A		����0����	R/W	
	0x006C		����1����	R/W	
	0x006E		����2����	R/W	
	0x0070		����3����	R/W	
	0x0072		0x0000	R/W	
	0x0074		��0x2013��	R/W	�������ڣ��꣨BCD�룩
	0x0076		��0x0616��	R/W	�������ڣ����գ�BCD�룩
	0x0078		��0x2013��	R/W	�������ڣ��꣨BCD�룩
	0x007A		��0x0620��	R/W	�������ڣ����գ�BCD�룩

	<<<<DO��>>>>	
MODBUS�����룺����Ȧ��1��					
���в�����Ϣ	
	0x0000	RS		R/W	�̵���״̬��0-�պϣ�1-�򿪣�
*/


/*
typedef struct Data{
	uint16_t		OCM;	// �������ģʽ��0-AO��1-DO��
	uint16_t		AM;		// �Զ�/�ֶ�ģʽ��0-�Զ���1-�ֶ���
	uint16_t		RH;		// �������ޣ�10m�� (1000��) 
	uint16_t		RL;		// �������ޣ�0m��  (1000��) 
	uint16_t		AH;		// �澯����	(1000��) 
	uint16_t		AL;		// �澯���� (1000��) 
	uint16_t		AHH;	// �澯������ (1000��) 
	uint16_t		ALL;	// �澯������ (1000��) 
	uint16_t		SV;		// �趨Һλ (1000��) 
	uint16_t		PV;		// ��ǰҺλ (1000��) 
	uint16_t		AOFR;	//AO�����������ƣ�0-����1-����
	uint16_t		DAMP;	//����ϵ�����˴���ʾ�����˲�ʱ�䳣����0��32s��
	
	uint16_t		MV;		// PID���ֵ�����ſ��ȣ�0��100%��
	uint16_t		P;		//��������
	uint16_t 		I;		//����ʱ��
	uint16_t 		D;		//΢��ʱ��
	uint16_t 		CO;		//�����������ź����
	uint16_t 		VI;		//��������ѹ�ź�����
	uint16_t 		PSP;	//24V��������
	uint16_t 		SVH;		//�趨Һλ���� ��DOʹ�ã�
	uint16_t 		SVL;		//�趨Һλ���� ��DOʹ�ã�
	uint16_t		VendorInfo[9];	//����������Ϣ���硰����ά�ɡ���
	uint16_t		ProductInfo[9];	//�ͺ���Ϣ���硰ABC-0123����
	
	uint16_t		ReleaseYear;	//�������ڣ��꣨BCD�룩
	uint16_t		ReleaseDate;	//�������ڣ����գ�BCD�룩
	uint16_t		QualifiedYear;	//�������ڣ��꣨BCD�룩
	uint16_t		QualifiedDate;	//�������ڣ����գ�BCD�룩	
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

