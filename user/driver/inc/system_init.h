#include "stm32f10x.h"
#include "fsmc_sram.h"
#include "platform_config.h"
#include "Stm32f10x_spi.h"
#include "Lcd_12864.h"

#define GPIO_INIT		0x0001
#define RTC_INIT	 	0x0002
#define USART_INIT		0x0004
#define FSCM_INIT		0x0008
#define FLASH_INIT		0x0010
#define RCC_INIT		0x0020
#define NVIC_INIT		0x0040
#define SYSTICK_INIT	0x0080
#define TIMER_INIT		0x0100
#define SPI_INIT		0x0101
#define DAC_INIT		0x0102
#define ADC_INIT		0x0104

void RCC_Configuration(void);
void GPIO_Configuration(void);

/* NVIC configuration */
void NVIC_Configuration(void);
void RTC_Configuration(void);
void SystemResourcesInit(uint32_t Device_Init);
void Flash_Configuration(uint8_t eraseFlag);

