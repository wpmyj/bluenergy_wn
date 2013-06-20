/**
  ******************************************************************************
  * @file lcd_12864.h
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Header for fsmc_sram.c file.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_spi.h"

/* LCD_RST */  
#define LCD_RST_SET		GPIO_SetBits(GPIOC, GPIO_Pin_7)			//PC7 
#define LCD_RST_RESET   GPIO_ResetBits(GPIOC, GPIO_Pin_7)		//PC7    
/* LCD_RS */ 
#define LCD_A0_SET     	GPIO_SetBits(GPIOA, GPIO_Pin_10)		//PC8 
#define LCD_A0_RESET    GPIO_ResetBits(GPIOA, GPIO_Pin_10)		//PC8    
/* LCD_CS */   
#define LCD_CS_SET     	GPIO_SetBits(GPIOA, GPIO_Pin_8)			//PA8 
#define LCD_CS_RESET    GPIO_ResetBits(GPIOA, GPIO_Pin_8)		//PA8    

#define COLUMN_SET_H	0x10
#define COLUMN_SET_L 	0x00
#define BASE_PAGE_ADDR 	0xb0

/* LCD Control Command */
#define DISPLAY_ON		0xaf
#define DISPLAY_OFF		0xae

#define RAM_START_ADDR	0x40

#define ADC_NORMAL		0xa0			//左右反转 正常
#define ADC_REVERSE		0xa1

#define DISPLAY_NORMAL  0xa6			//反白效果 正常
#define DISPLAY_REVERSE 0xa7

#define DISPLAY_ALL_POINT_ON  	0xa5
#define DISPLAY_ALL_POINT_OFF  	0xa4	//全屏显示 关

#define	LCD_BIAS_SET_9 	0xa2			//LCD 的偏压比 1/9
#define	LCD_BIAS_SET_7	0xa3

#define	OUTPUT_MODE_NORMAL	0xc0	
#define	OUTPUT_MODE_REVERSE	0xc8		//上下反转 反向

#define	INNER_POWER_ON	0x2f			//开关内部电路的电源

#define	V0				0x24	//对比度(0X24 是比较合适)
#define	LIGHT_SET		0x81	//亮度设定入口
#define	LIGHT_VALUE		0x24	//亮度值 

/* Exported types ------------------------------------------------------------*/
typedef struct                 // 汉字字模数据结构			
{
	uint8_t x;               // 汉字内码索引
    uint8_t y;                       // 点阵码数据
    uint8_t length;
	uint8_t data[16];
} DisplayInfo;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* functions ---------------------------------------------------------*/
void lcdWriteCom(uint8_t command);
void lcdInit(void);
void lcdWriteData(uint8_t data);
void cleanScreen(void);
void fullScreenDisplay(unsigned char *pic);
void displayOne16x16(DisplayInfo displayInfo);
void displayOneLine16x16(DisplayInfo displayInfo);
void displayOneLine24x32(DisplayInfo displayInfo);
void getNum(unsigned int, uint8_t scale, uint8_t *rValue);
void displayOneLine24x32_with_params(uint8_t x, uint8_t y, uint8_t length, uint8_t *data);

