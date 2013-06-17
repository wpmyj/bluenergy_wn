#define GB2432_MAXSIZE		11
#define GB2432_SIZE			96

typedef enum characterSetTypes {ASCII8x16,GB16x16, GB24x32} characterSetTypes;
typedef struct
{
	uint8_t width;
	uint8_t hight;
	characterSetTypes type;
} Character;

const Character character[3] = {
8, 16, ASCII8x16,
16, 16, GB16x16,
24, 32, GB24x32
};

typedef struct
{
	uint8_t position_x;
	uint8_t position_y;
	uint8_t length;
	characterSetTypes type;
} DisplayItem;

static DisplayItem companyName = 
{
	0,
	0,
	6,
	ASCII8x16	
};

typedef struct                 // 汉字字模数据结构			
{
	uint8_t Index;               // 汉字内码索引
    char Msk[96];                       // 点阵码数据
} typFNT_GB2432;

extern const typFNT_GB2432 tGB_24[GB2432_MAXSIZE] = {
'0', 0x80,0x00,0x00,0x00,0x00,0xC0,0xF0,0xF0,0xF8,0x1C,0x04,0x04,0x04,0x04,0x1C,0xF8,
	 0xF0,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,
	 0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
	 0xFF,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x0F,
	 0x1F,0x38,0x20,0x20,0x20,0x20,0x38,0x1F,0x0F,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,
	 
'1', 0x00,0x00,0x00,0x00,0x00,0x40,0x20,0x20,0x60,0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0x00,
 	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 	 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
 	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x20,
 	 0x30,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x30,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,

'2', 0x00,0x00,0x00,0x80,0xC0,0xF0,0x70,0x78,0x7C,0x7C,0x7C,0xFC,0xFC,0xFC,0xF8,0xF8,
	 0xF0,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x01,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x83,0xFF,0xFF,0xFF,0xFF,0x3F,0x0F,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0x78,0x3C,0x1F,0x0F,0x03,0x01,
	 0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x30,0x38,0x3C,0x3E,0x3F,
	 0x3F,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3F,0x03,0x00,0x00,0x00,0x00,

'3', 0x00,0x00,0x00,0x40,0x60,0x30,0x18,0x18,0x18,0x1C,0x1C,0x3C,0x7C,0xFC,0xFC,0xF8,
	 0xF8,0xF0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x40,0xC0,0xE0,0xF0,0xF8,0xFF,0xFF,0xEF,0xE7,0xC3,0x81,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x0F,0xFF,0xFF,
	 0xFF,0xFF,0xFF,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x1F,0x3F,0x3F,0x3E,
	 0x3C,0x38,0x38,0x38,0x1C,0x1E,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,
	
'4', 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xF0,0xF8,0xFC,
	 0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x20,
	 0x18,0x04,0x02,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0xF8,0xF4,0xF2,0xF1,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,
	 0xFF,0xFF,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,

'5', 0x00,0x00,0x00,0x00,0x00,0xC0,0x78,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,
	 0x7C,0x7C,0x3C,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x78,0x7F,0x7E,0x7E,0x7E,
	 0xFE,0xFE,0xFC,0xFC,0xFC,0xF8,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x07,0x0F,
	 0x3F,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x1F,0x1F,0x3F,0x3E,0x3C,
	 0x3C,0x38,0x30,0x20,0x20,0x20,0x20,0x10,0x18,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,

'6', 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0x70,0x38,0x38,0x18,0x08,
	 0x0C,0x0C,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xF0,0xFC,0xFE,0xFF,0xFF,
	 0x3F,0x23,0x20,0x20,0x60,0xE0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,
	 0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x0F,0x1F,0x1F,
	 0x3F,0x38,0x20,0x20,0x20,0x38,0x1F,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,

'7', 0x00,0x00,0x00,0xF0,0xFC,0xFC,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,0x7C,
	 0xFC,0xFC,0xFC,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x01,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0xC0,0xF8,0xFF,0x3F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xF0,0xFE,0x7F,0x0F,0x01,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x20,0x3C,0x3F,0x1F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

'8', 0x00,0x00,0x80,0xE0,0xF0,0xF8,0xF8,0xFC,0x1C,0x0C,0x04,0x04,0x04,0x0C,0x1C,0xF8,
	 0xF8,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,
	 0xFE,0xFC,0xF8,0xF0,0xE0,0xF0,0xF8,0xBF,0x9F,0x1F,0x0F,0x03,0x00,0x00,0x00,0x00,
	 0x00,0x00,0xE0,0xF8,0xFC,0xFC,0xFE,0x0E,0x03,0x03,0x03,0x07,0x1F,0x3F,0xFF,0xFF,
	 0xFF,0xFF,0xFC,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x0F,0x1F,0x1F,0x38,
	 0x30,0x20,0x20,0x20,0x30,0x38,0x1F,0x1F,0x0F,0x0F,0x07,0x01,0x00,0x00,0x00,0x00,

'9', 0x00,0x00,0x00,0xC0,0xE0,0xF0,0xF8,0xF8,0x1C,0x04,0x04,0x04,0x0C,0xFC,0xF8,0xF8,
	 0xF0,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,
	 0xC0,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x07,0x06,0x04,0x04,0xC4,0xFC,0xFF,0xFF,
	 0x7F,0x3F,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x30,0x30,0x10,0x18,
	 0x1C,0x1C,0x0E,0x0F,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

'.', 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x3F,0x3F,0x3F,0x1F,
	 0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
