/**
  ******************************************************************************
  * @file FSMC/SRAM/fsmc_sram.c 
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
#include "usart.h"

/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
void usartSendData(uint8_t data)
{
	USART_SendData(USART2, data);                 					//发送一字节数据
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

void RS485_RW_Select(uint8_t chanel)
{
	if(chanel == RS485_READ)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
	else if(chanel == RS485_WRITE)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}	
}

