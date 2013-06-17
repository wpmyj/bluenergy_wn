/**
  ******************************************************************************
  * @file RTC/Calendar/main.c
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main program body
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
#include "include.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TxBufferSize   (sizeof(TxBuffer))                  //统计发送数组元素个数
#define RxBufferSize   (sizeof(TxBuffer))                  //接收数组元素个数与发送数组一致


#ifdef _GNUC_
#define PUTCHAR_PROTOTYPE int _io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
extern uint8_t KeyID[8];
uint8_t TxBuffer[8];     //发送数组
uint8_t RxBuffer[RxBufferSize];                      //接收数组
uint8_t DataSizeOfTransfer = 5;           //发送数据量等于发送数组元素个数
uint8_t DataSizeOfReceiver = RxBufferSize;           //接收数据量等于接收数组元素个数
uint8_t ACK_Data[6] = {0x7e, 0x00, 0x00, 0x01, 0x00, 0x00};
ComDataStruct ComData;
extern unsigned char gBattery[6][4608], gLock[3][4608]; 
                            
FlashDataInfoData_16 FLSH_PicData = {0x08040000, 0x08065fff, 77823, 0};

TMR       TmrTbl[TMR_MAX_TMR];          /* Table of timers managed by this module             */

/* Private function prototypes -----------------------------------------------*/
void uDelay(uint16_t nTime);
void delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

static  void  ConmmunctionTimer (void *arg)
{
    arg = arg;
    ComData.CheckSum = 0;
    ComData.ComState = START;
    ComData.LenNum = 0;
    ComData.DataCount = 0;
    ComData.Length = 0;
    ComData.LastSeq = 0;
    ComData.Seq = 0;
    ComData.RevOK = REV_NORMAL;
}


TmrTaskConfig(void)
{
    TmrInit();
    TmrCfgFnct(FALSE, 0, ConmmunctionTimer, (void *)0);                  /* Execute when Timer #0 times out          */
	TmrSetMST(0, 0, 10, 0);                                 /* Set timer #0 to 0 min., 10 sec. 0/10 sec. */
    TmrStart(0);
}

/*******************************************************************************
* Function Name  : Time_Adjust
* Description    : Adjusts time.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Time_Reset(void)
{
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Change the current time */
    RTC_SetCounter(0);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}

unsigned char niu[1024] = {  
0X01,0X01,0X55,0X00,0X40,0X00,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X3F,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0XFF,0X9F,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0XFF,
0X8E,0X9F,0X8C,0XFF,0XFF,0XFF,0XFF,0XFF,0X06,0X03,0X05,0XFF,0XFF,0XFF,0XFF,0XFF,
0X0E,0X03,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0X01,0X8D,0XFF,0XFF,0XFF,0XFF,0XFF,
0X82,0XF0,0XCD,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFC,0X20,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XBF,0X9F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XAF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFE,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XF1,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X8F,0XF3,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0X8F,0XF7,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XCF,0XFE,0X9F,0XFF,0XFF,0XFF,0XFF,0XFF,0XCF,0XFE,0X1F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XCD,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0X8D,0XFC,0X1F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XCD,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0X8D,0XFC,0X1F,0XFF,
0XFF,0XFF,0XFF,0XFF,0X1D,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0X8D,0XFC,0X1F,0XDF,
0XFF,0XFF,0XFF,0XFF,0XDD,0XF4,0X1F,0XDF,0XFF,0XFF,0XFF,0XFF,0XCF,0XF4,0X1F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XEF,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0XFD,0X3F,0XFF,
0XFF,0XFF,0XFF,0XFD,0XDF,0XFD,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XFD,0XBF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0XFF,0X07,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,
0X00,0X30,0X1F,0XEF,0XFF,0XFF,0X3F,0XFF,0X00,0X00,0X18,0X43,0X9F,0XFC,0X3F,0XFF,
0X00,0X00,0X00,0X03,0XFB,0XFC,0X3F,0XFF,0X00,0X00,0X00,0X03,0X1B,0XFC,0X3F,0XFF,
0X00,0X00,0X10,0X03,0X1B,0XFC,0X3F,0XFF,0X00,0X00,0X10,0X03,0X1B,0XFC,0X76,0XFF,
0X00,0X00,0X11,0X03,0X1B,0XFC,0XED,0XFF,0X00,0X00,0X10,0X03,0X1F,0XFF,0XFB,0XFF,
0X00,0X00,0X00,0X03,0X0F,0X3F,0XF9,0XFF,0X00,0X10,0X00,0X02,0X0C,0X7F,0XFF,0XFF,
0X00,0X00,0X00,0X03,0X0F,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X02,0X1F,0XFF,0XFF,0XFF,
0X00,0X00,0X00,0X02,0X3F,0XFF,0XFF,0XBF,0X00,0X00,0X00,0X02,0X3F,0XFF,0XFF,0XFF,
0X00,0X00,0X00,0X02,0X7F,0XFF,0XFF,0XBF,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,
0X00,0X00,0X00,0X01,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X3E,0X67,0XFF,0X7F,0XFF,0XFF,
0X02,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1C,0X00,0XFF,0X7F,0XFF,0XFF,0XFF,0XFF,
0X0C,0X01,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0X1F,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X1E,0XF3,0XF7,0X7F,0XFF,0XFF,0XFF,0XFF,0X3C,0XFB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X7B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,
0XEF,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCF,0XFF,0XFF,0XFF,0XEF,0XFF,0XFF,0XFF,
0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF 
};  

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{
    SystemResourcesInit(RCC_INIT 
                        | FLASH_INIT
                        | USART_INIT
                        | GPIO_INIT
                        | SYSTICK_INIT
                        | TIMER_INIT
                        | SPI_INIT);
	LCD_RST_RESET;
  	delay(2);
  	LCD_RST_SET;
  	delay(2);

	lcdInit();	
    TmrTaskConfig();
	cleanScreen();
	//fullScreenDisplay(niu);
	displayOneLineOfChineseCharacter(0, 0, 6, "西安维纳测控");	
	displayOneLine2432Character(0, 4, 5, "0.345");
    while(1)
    {
    	//TmrTask(0);
	}
}

/*******************************************************************************
* Function Name  : PUTCHAR_PROTOTYPE
* Description    : 重定义C语言的fprint函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
PUTCHAR_PROTOTYPE

{
    /* Write a character to the USART */
    USART_SendData(USART1, (uint8_t)ch);

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ;

    return ch;
}

/**
 * @brief  Inserts a delay time.
 * @param nTime: specifies the delay time length, in milliseconds.
 * @retval : None
 */
void delay(__IO uint32_t nTime)
{
    TimingDelay = nTime;

    while(TimingDelay != 0);
}

/**
 * @brief  Inserts a delay time.
 * @param nTime: specifies the delay time length, in milliseconds.
 * @retval : None
 */
void uDelay(uint16_t nTime)
{
    uint16_t TIMCounter = nTime;

    TIM_Cmd(TIM2, ENABLE);
    TIM_SetCounter(TIM2, TIMCounter);
    while (TIMCounter > 1)
    {
        TIMCounter = TIM_GetCounter(TIM2);
    }
    TIM_Cmd(TIM2, DISABLE);
}

/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval : None
*/
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1)
    {}
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
