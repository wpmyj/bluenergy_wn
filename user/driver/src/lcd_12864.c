/**
  ******************************************************************************
  * @file lcd_12864.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  This file provides a set of functions needed to drive the 
  *         IS61WV51216BLL SRAM memory mounted on STM3210E-EVAL board.
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

/* Includes ------------------------------------------------------------------*/
#include "Include.h"
#include "GB1616.h"
#include "GB1216.h"
#include "GB2432.h"
#include "ascii_12x16.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void GetGB1616(uint8_t code[2], const typFNT_GB1616 GB_16[],uint8_t gb[2][16]);
void GetGB2432(uint8_t code, const typFNT_GB2432 GB_2432[],uint8_t gb[4][24]);
void SetBaseXY(uint8_t startX, uint8_t startY);
void GetGB1216(uint8_t ch, const uint8_t gb12x16[][24], uint8_t ascii[2][12]);
void GetAscii1216(char ch, const unsigned char ascii12x16[][24], uint8_t ascii[2][12]);

/* Private function prototypes -----------------------------------------------*/
void LcdInit()
{		
	LCD_RST_RESET;
  	delay(5);
  	LCD_RST_SET;
  	delay(5);

	LcdWriteCom(DISPLAY_ON);			//Display on
  	LcdWriteCom(RAM_START_ADDR);		//RAM起始地址
  	LcdWriteCom(ADC_REVERSE);			//左右反转 正常    
  	LcdWriteCom(DISPLAY_NORMAL);		//反白效果 正常 
  	LcdWriteCom(DISPLAY_ALL_POINT_OFF);	//全屏显示 关
  	LcdWriteCom(LCD_BIAS_SET_9);		//LCD 的偏压比 1/9  
  	LcdWriteCom(OUTPUT_MODE_NORMAL);	//上下反转 反向
  	LcdWriteCom(INNER_POWER_ON);		//开关内部电路的电源 
  	LcdWriteCom(V0);					//对比度(0X24 是比较合适)
  	LcdWriteCom(LIGHT_SET);				//亮度设定入口 
  	LcdWriteCom(LIGHT_VALUE);			//亮度值 
  	LcdWriteCom(RAM_START_ADDR);		//RAM起始地址
}

void LcdWriteCom(uint8_t command) 
{  
	LCD_CS_RESET;  						//片选拉低，选中LCD 
	LCD_A0_RESET;    	//设置为写命令    
	SPI_I2S_SendData(SPI2, command);	//SPI写数据   
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);	//等待发送完�
	LCD_CS_SET;     //片选拉高，释放LCD  �   
}

void LcdWriteData(uint8_t data)
{ 
	LCD_CS_RESET;  						//片选拉低，选中LCD 
	LCD_A0_SET;   //设置为写数据    
	SPI_I2S_SendData(SPI2, data); //SPI写数据   
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET); //等待发送完成  
	LCD_CS_SET;     //片选拉高，释放LCD  
}

void CleanScreen()
{
	uint8_t page, i;

	
	for(page = 0; page < 8; page++)
	{
		LcdWriteCom(BASE_PAGE_ADDR + page);
		SetBaseXY(4, 0);
		for(i = 0; i< 128; i++) 
		{
	  		LcdWriteData(0x00);
	 	}
	}
}

void FullScreenDisplay(uint8_t *pic)
{
	uint8_t page, i;

	for(page = 0; page < 8; page++)
	{
		LcdWriteCom(BASE_PAGE_ADDR + page);
		LcdWriteCom(COLUMN_SET_H);		//列高4位
		LcdWriteCom(COLUMN_SET_L);		//列低4位（A3-A0）
		for(i = 0; i< 128; i++) 
		{
	  		LcdWriteData(*pic++);
	 	}
	}

}

void DisplayOne12x16(uint8_t x, uint8_t y, char ch, bool inverse)
{
	uint8_t i;	
	uint8_t page;
	uint8_t ascii[2][12];

	GetAscii1216(ch, ascii_12x16, ascii);

	for(page = 0; page < 2; page++)
	{
		SetBaseXY(x, y);
		LcdWriteCom(BASE_PAGE_ADDR + page + y);
		for(i = 0; i< 12; i++) 
		{
	  		LcdWriteData((inverse == TRUE) ? ~ascii[page][i] : ascii[page][i]);
	 	}
	}
}

void DisplayOne16x16(DisplayInfo displayInfo)
{
	uint8_t i;	
	uint8_t page;
	uint8_t gb[2][16];

	GetGB1616(displayInfo.data, tGB_16, gb);

	for(page = displayInfo.y; page < displayInfo.y + 2; page++)
	{
		SetBaseXY(displayInfo.x, displayInfo.y);
		LcdWriteCom(BASE_PAGE_ADDR + page);
		for(i = 0; i< 16; i++) 
		{
	  		LcdWriteData(gb[page][i]);
	 	}
	}
}

void DisplayOneLine16x16(DisplayInfo displayInfo)
{
	uint8_t i, k;	
	uint8_t page;
	uint8_t gb[2][16];
	
	for(page = 0; page < 2; page++)
	{		
		SetBaseXY(displayInfo.x, displayInfo.y);
		LcdWriteCom(BASE_PAGE_ADDR + page + displayInfo.y);
		for(i = 0; i < displayInfo.length; i++)
		{
			GetGB1616(displayInfo.data + i * 2, tGB_16, gb);

			for(k = 0; k < 16; k++)
			{
				LcdWriteData(gb[page][k]);
			}			
		}
	}
}

void DisplayOneLine12x16_with_params(uint8_t x, uint8_t y, uint8_t length, char *data, bool selected)
{
	uint8_t i, k;	
	uint8_t page;
	uint8_t ascii[2][12];
	
	for(page = 0; page < 2; page++)
	{		
		SetBaseXY(x, y);
		LcdWriteCom(BASE_PAGE_ADDR + page + y);
		for(i = 0; i < length; i++)
		{
			GetAscii1216(data[i], ascii_12x16, ascii);
			for(k = 0; k < 12; k++)
			{
				LcdWriteData((selected == TRUE) ? ~ascii[page][k] : ascii[page][k]);
			}			
		}
	}
}

void DisplayOneLine16x16_with_params(uint8_t x, uint8_t y, uint8_t length, uint8_t *data, bool selected)
{
	uint8_t i, k;	
	uint8_t page;
	uint8_t gb[2][16];
	
	for(page = 0; page < 2; page++)
	{		
		SetBaseXY(x, y);
		LcdWriteCom(BASE_PAGE_ADDR + page + y);
		for(i = 0; i < length; i++)
		{
			GetGB1616(data + i * 2, tGB_16, gb);

			for(k = 0; k < 16; k++)
			{
				LcdWriteData((selected == TRUE) ? ~gb[page][k] : gb[page][k]);
			}			
		}
	}
}

void DisplayOneGB12x16(uint8_t x, uint8_t y, uint8_t index, bool inverse)
{
	uint8_t i;	
	uint8_t page;
	uint8_t gb[2][12];

	GetGB1216(index, GB_1216, gb);
	for(page = 0; page < 2; page++)
	{
		SetBaseXY(x, y);
		LcdWriteCom(BASE_PAGE_ADDR + page + y);
		for(i = 0; i< 12; i++) 
		{
	  		LcdWriteData((inverse == TRUE) ? ~gb[page][i] : gb[page][i]);
	 	}
	}
}

void DisplayOne24x32(uint8_t x, uint8_t y, char ch, bool inverse)
{
	uint8_t i;	
	uint8_t page;
	uint8_t gb[4][24];

	GetGB2432(ch, tGB_24, gb);
	for(page = 0; page < 4; page++)
	{
		SetBaseXY(x, y);
		LcdWriteCom(BASE_PAGE_ADDR + page + y);
		for(i = 0; i< 24; i++) 
		{
	  		LcdWriteData((inverse == TRUE) ? ~gb[page][i] : gb[page][i]);
	 	}
	}
}

void DisplayOneLine24x32(DisplayInfo displayInfo)
{
	uint8_t i, k;	
	uint8_t page;
	uint8_t gb[4][24];
	
	for(page = 0; page < 4; page++)
	{		
		SetBaseXY(displayInfo.x, displayInfo.y);
		LcdWriteCom(BASE_PAGE_ADDR + page + displayInfo.y);
		for(i = 0; i < displayInfo.length; i++)
		{
			GetGB2432(displayInfo.data[i], tGB_24, gb);

			for(k = 0; k < GB2432_SIZE / 4; k++)
			{
				LcdWriteData(gb[page][k]);
			}			
		}
	}
}

void DisplayOneLine24x32_with_params(uint8_t x, uint8_t y, uint8_t length, uint8_t *data)
{
	uint8_t i, k;	
	uint8_t page;
	uint8_t gb[4][24];
	
	for(page = 0; page < 4; page++)
	{		
		SetBaseXY(x, y);
		LcdWriteCom(BASE_PAGE_ADDR + page + y);
		for(i = 0; i < length; i++)
		{
			GetGB2432(data[i], tGB_24, gb);

			for(k = 0; k < GB2432_SIZE / 4; k++)
			{
				LcdWriteData(gb[page][k]);
			}			
		}
	}
}

/* Private func */

void SetBaseXY(uint8_t startX, uint8_t startY)
{
	//LcdWriteCom(RAM_START_ADDR + 63 - startY);		//RAM起始地址
	LcdWriteCom(COLUMN_SET_H + ((startX & 0xf0) >> 4));	//列高4位
	LcdWriteCom(COLUMN_SET_L + (startX & 0x0f));		//列低4位（A3-A0）
}

void GetAscii1216(char ch, const unsigned char ascii12x16[][24], uint8_t ascii[2][12])
{
	memcpy(ascii, ascii12x16[ch - ' '], ASCII1216_SIZE);				  	
}

void GetGB1216(uint8_t ch, const uint8_t gb12x16[][24], uint8_t ascii[2][12])
{
	memcpy(ascii, gb12x16[ch], GB1216_SIZE);				  	
}


void GetGB1616(uint8_t code[2], const typFNT_GB1616 GB_16[], uint8_t gb[2][16])
{
	uint8_t k;
	for (k = 0; k < GB1616_MAXSIZE; k++) //64标示自建汉字库中的个数，循环查询内码
    {
        if ((GB_16[k].Index[0] == code[0]) && (GB_16[k].Index[1] == code[1]))
        {
            memcpy(gb, GB_16[k].Msk, GB1616_SIZE);			
		}
    }							  	
}

void GetGB2432(uint8_t code, const typFNT_GB2432 GB_2432[], uint8_t gb[4][24])
{
	uint8_t k;
	
	for (k = 0; k < GB2432_MAXSIZE; k++) //64标示自建汉字库中的个数，循环查询内码
    {
        if (GB_2432[k].Index == code)
        {
            memcpy(gb, GB_2432[k].Msk, GB2432_SIZE);			
		}
    }
							  	
}

void GetNum(unsigned int num, uint8_t scale, uint8_t *rValue)
{	
	uint8_t i, j, length = 0;
	unsigned int res = num;
	uint8_t numOfString[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
	unsigned int level[5] = {1, 10, 100, 1000, 10000};
	
	while(res)
	{
		res /= 10;
		length++;
	}

	for(i = 0, j = 0; i < length; i++, j++)
	{
		if(i == length - scale)
		{
			rValue[j] = numOfString[10];
			j++;
		}
		rValue[j] = numOfString[num / (level[length - i - 1])];

		num %= level[length - i - 1];
	}
	
}

