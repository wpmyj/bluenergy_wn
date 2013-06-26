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
#include "GB2432.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
uint8_t *GetGB1616(uint8_t code[2], const typFNT_GB1616 GB_16[]);
uint8_t *GetGB2432(uint8_t code, const typFNT_GB2432 GB_2432[]);
void SetBaseXY(uint8_t startX, uint8_t startY);
void Copy(uint8_t *src, uint8_t *dst, uint8_t times, uint8_t offset);


/* Private function prototypes -----------------------------------------------*/
void LcdInit()
{		
	LCD_RST_RESET;
  	delay(5);
  	LCD_RST_SET;
  	delay(5);

	LcdWriteCom(DISPLAY_ON);			//Display on
  	LcdWriteCom(RAM_START_ADDR);		//RAMÆðÊ¼µØÖ·
  	LcdWriteCom(ADC_REVERSE);			//×óÓÒ·´×ª Õý³£    
  	LcdWriteCom(DISPLAY_NORMAL);		//·´°×Ð§¹û Õý³£ 
  	LcdWriteCom(DISPLAY_ALL_POINT_OFF);	//È«ÆÁÏÔÊ¾ ¹Ø
  	LcdWriteCom(LCD_BIAS_SET_9);		//LCD µÄÆ«Ñ¹±È 1/9  
  	LcdWriteCom(OUTPUT_MODE_NORMAL);	//ÉÏÏÂ·´×ª ·´Ïò
  	LcdWriteCom(INNER_POWER_ON);		//¿ª¹ØÄÚ²¿µçÂ·µÄµçÔ´ 
  	LcdWriteCom(V0);					//¶Ô±È¶È(0X24 ÊÇ±È½ÏºÏÊÊ)
  	LcdWriteCom(LIGHT_SET);				//ÁÁ¶ÈÉè¶¨Èë¿Ú 
  	LcdWriteCom(LIGHT_VALUE);			//ÁÁ¶ÈÖµ 
  	LcdWriteCom(RAM_START_ADDR);		//RAMÆðÊ¼µØÖ·
}

void LcdWriteCom(uint8_t command) 
{  
	LCD_CS_RESET;  						//Æ¬Ñ¡À­µÍ£¬Ñ¡ÖÐLCD 
	LCD_A0_RESET;    	//ÉèÖÃÎªÐ´ÃüÁî    
	SPI_I2S_SendData(SPI2, command);	//SPIÐ´Êý¾Ý   
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);	//µÈ´ý·¢ËÍÍê³
	LCD_CS_SET;     //Æ¬Ñ¡À­¸ß£¬ÊÍ·ÅLCD  É   
}

void LcdWriteData(uint8_t data)
{ 
	LCD_CS_RESET;  						//Æ¬Ñ¡À­µÍ£¬Ñ¡ÖÐLCD 
	LCD_A0_SET;   //ÉèÖÃÎªÐ´Êý¾Ý    
	SPI_I2S_SendData(SPI2, data); //SPIÐ´Êý¾Ý   
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET); //µÈ´ý·¢ËÍÍê³É  
	LCD_CS_SET;     //Æ¬Ñ¡À­¸ß£¬ÊÍ·ÅLCD  
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
		LcdWriteCom(COLUMN_SET_H);		//ÁÐ¸ß4Î»
		LcdWriteCom(COLUMN_SET_L);		//ÁÐµÍ4Î»£¨A3-A0£©
		for(i = 0; i< 128; i++) 
		{
	  		LcdWriteData(*pic++);
	 	}
	}

}

void DisplayOne16x16(DisplayInfo displayInfo)
{
	uint8_t *gb1616, i;	
	uint8_t page;
	uint8_t gb[2][16];

	gb1616 = GetGB1616(displayInfo.data, tGB_16);
	Copy(gb1616, gb[0], 2, GB1616_SIZE);

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
	uint8_t *gb1616, i, k;	
	uint8_t page;
	uint8_t gb[2][16];
	
	for(page = 0; page < 2; page++)
	{		
		SetBaseXY(displayInfo.x, displayInfo.y);
		LcdWriteCom(BASE_PAGE_ADDR + page + displayInfo.y);
		for(i = 0; i < displayInfo.length; i++)
		{
			gb1616 = GetGB1616(displayInfo.data + i * 2, tGB_16);
			Copy(gb1616, gb[0], 2, GB1616_SIZE);
			for(k = 0; k < 16; k++)
			{
				LcdWriteData(gb[page][k]);
			}			
		}
	}
}

void DisplayOneLine16x16_with_params(uint8_t x, uint8_t y, uint8_t length, uint8_t *data, bool selected)
{
	uint8_t *gb1616, i, k;	
	uint8_t page;
	uint8_t gb[2][16];
	
	for(page = 0; page < 2; page++)
	{		
		SetBaseXY(x, y);
		LcdWriteCom(BASE_PAGE_ADDR + page + y);
		for(i = 0; i < length; i++)
		{
			gb1616 = GetGB1616(data + i * 2, tGB_16);
			Copy(gb1616, gb[0], 2, GB1616_SIZE);
			for(k = 0; k < 16; k++)
			{
				LcdWriteData((selected == TRUE) ? ~gb[page][k] : gb[page][k]);
			}			
		}
	}
}


void DisplayOneLine24x32(DisplayInfo displayInfo)
{
	uint8_t *gb2432, i, k;	
	uint8_t page;
	uint8_t gb[4][24];
	
	for(page = 0; page < 4; page++)
	{		
		SetBaseXY(displayInfo.x, displayInfo.y);
		LcdWriteCom(BASE_PAGE_ADDR + page + displayInfo.y);
		for(i = 0; i < displayInfo.length; i++)
		{
			gb2432 = GetGB2432(displayInfo.data[i], tGB_24);
			Copy(gb2432, gb[0], 4, GB2432_SIZE);
			for(k = 0; k < GB2432_SIZE / 4; k++)
			{
				LcdWriteData(gb[page][k]);
			}			
		}
	}
}

void DisplayOneLine24x32_with_params(uint8_t x, uint8_t y, uint8_t length, uint8_t *data)
{
	uint8_t *gb2432, i, k;	
	uint8_t page;
	uint8_t gb[4][24];
	
	for(page = 0; page < 4; page++)
	{		
		SetBaseXY(x, y);
		LcdWriteCom(BASE_PAGE_ADDR + page + y);
		for(i = 0; i < length; i++)
		{
			gb2432 = GetGB2432(data[i], tGB_24);
			Copy(gb2432, gb[0], 4, GB2432_SIZE);
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
	//LcdWriteCom(RAM_START_ADDR + 63 - startY);		//RAMÆðÊ¼µØÖ·
	LcdWriteCom(COLUMN_SET_H + ((startX & 0xf0) >> 4));	//ÁÐ¸ß4Î»
	LcdWriteCom(COLUMN_SET_L + (startX & 0x0f));		//ÁÐµÍ4Î»£¨A3-A0£©
}

void Copy(uint8_t *src, uint8_t *dst, uint8_t times, uint8_t size)
{
	uint8_t i, offset = size / times;
	for(i = 0; i < times; i++)
	{
		memcpy(dst + i * offset, src + i * offset, offset);
	}
}

uint8_t *GetGB1616(uint8_t code[2], const typFNT_GB1616 GB_16[])
{
	uint8_t gb16[GB1616_SIZE], k;
	for (k = 0; k < GB1616_MAXSIZE; k++) //64±êÊ¾×Ô½¨ºº×Ö¿âÖÐµÄ¸öÊý£¬Ñ­»·²éÑ¯ÄÚÂë
    {
        if ((GB_16[k].Index[0] == code[0]) && (GB_16[k].Index[1] == code[1]))
        {
            memcpy(gb16, GB_16[k].Msk, GB1616_SIZE);			
		}
    }
	return gb16;							  	
}

uint8_t *GetGB2432(uint8_t code, const typFNT_GB2432 GB_2432[])
{
	uint8_t gb2432[GB2432_SIZE], k;
	
	for (k = 0; k < GB2432_MAXSIZE; k++) //64±êÊ¾×Ô½¨ºº×Ö¿âÖÐµÄ¸öÊý£¬Ñ­»·²éÑ¯ÄÚÂë
    {
        if (GB_2432[k].Index == code)
        {
            memcpy(gb2432, GB_2432[k].Msk, GB2432_SIZE);			
		}
    }
	return gb2432;							  	
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

