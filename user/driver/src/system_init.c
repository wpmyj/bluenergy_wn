#include "include.h"

ErrorStatus HSEStartUpStatus;
GPIO_InitTypeDef GPIO_InitStructure;

/**
  * @brief  Configures the SysTick.
  * @param  None
  * @retval : None
  */
void SysTick_Configuration(void)
{
	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config((SystemFrequency) / 1000))
	{
		/* Capture error */
		while (1);
	}
	NVIC_SetPriority(SysTick_IRQn, 0x0);
}

/**
  * @brief  Configures the NVOC of USART.
  * @param  None
  * @retval : None
  */
USARTx_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
#ifdef  VECT_TAB_RAM
	/* Set the Vector Table base location at 0x20000000 */
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configures the GPIO of USART.
  * @param  None
  * @retval : None
  */
USART_GPIO_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //时钟速度为50M
	/* USART Configuration  */
	/*配置USART2(串口2)所用IO口*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                   //发送脚为PA9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);                      //用以上几个参数初始化PA口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                  //接收脚为PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //复用开漏输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);                      //用以上几个参数初始化PA口
}

/**
  * @brief  Configures the USART.
  * @param  None
  * @retval : None
  */
void USARTx_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	/* (1) ---- Enable USART2, GPIOA, 打开串口2 和GPIOA时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	/* (2) ----  配置USART1中断*/
	USARTx_NVIC_Init();
	/* (3) ---- 配置USART1(串口1)所用IO口*/
	USART_GPIO_Init();
	/* (4) ---- USART
	  - USART2 configured as follow:
	  - 波特率 = 115200 baud
	  - 字长 = 8 Bits
	  - 一个停止位
	  - 无校验位
	  - 关闭数据流控制 (RTS and CTS signals)
	*/
	USART_InitStructure.USART_BaudRate = 9600;                   //设置串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;    //设置数据长度为8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;         //设置一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;           //无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//禁止硬件流控制模式
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //打开串口的收发功能
	/* 配置USART2 */
	USART_Init(USART2, &USART_InitStructure);                      //用以上参数初始化USART2
	/* 配置串口1接收中断 */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                 //打开接收中断
	/*使能串口2 */
	USART_Cmd(USART2, ENABLE);                                     //打开串口2
	USART_ClearFlag(USART2, USART_FLAG_TC);
}

/**
  * @brief  Configures the GPIO of FSCM.
  * @param  None
  * @retval : None
  */
void FSCM_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //时钟速度为50M
	/* FSCM Configuration  */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
						   RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                 //LCD-RST
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                 //LCD-RST
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
								  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
								  GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
	  PE.14(D11), PE.15(D12) as alternate function push pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
								  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
								  GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/* NE1 configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* RS */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_7);          //CS=1
	GPIO_SetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_0 | GPIO_Pin_1);
	GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);        //RESET=0
	GPIO_SetBits(GPIOD, GPIO_Pin_4);          //RD=1
	GPIO_SetBits(GPIOD, GPIO_Pin_5);          //WR=1
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
}

/**
  * @brief  Configures the FSCM.
  * @param  None
  * @retval : None
  */
void FSCM_Configuration(void)
{
	/*配置FSCM所用IO口*/
	FSCM_GPIO_Init();
	/* Enable the FSMC Clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
}

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval : None
  */
void RTC_Configuration(void)
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);
	/* Reset Backup Domain */
	BKP_DeInit();
	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{} 
	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);
	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval : None
  */
void NVIC_Configuration(void)
{
}

void RCC_Internal_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;

	//将外设 RCC寄存器重设为缺省值

	RCC_DeInit();

	RCC_HSICmd(ENABLE);

	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	if(HSEStartUpStatus == SUCCESS) 
	{

		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		RCC_PCLK2Config(RCC_HCLK_Div1);

		RCC_PCLK1Config(RCC_HCLK_Div2);

		//设置 PLL 时钟源及倍频系数

		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_2);

		//使能或者失能 PLL,这个参数可以取：ENABLE或者DISABLE

		RCC_PLLCmd(ENABLE);//如果PLL被用于系统时钟,那么它不能被失能

		//等待指定的 RCC 标志位设置成功 等待PLL初始化成功

		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		//设置系统时钟（SYSCLK） 设置PLL为系统时钟源

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		//等待PLL成功用作于系统时钟的时钟源

		// 0x00：HSI 作为系统时钟

		// 0x04：HSE作为系统时钟

		// 0x08：PLL作为系统时钟

		while(RCC_GetSYSCLKSource() != 0x08);
	}
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();                                             //时钟控制寄存器全部恢复默认值
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);                                //外部高速时钟源开启（8M晶振）
	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();               //等待外部时钟就绪
	if(HSEStartUpStatus == SUCCESS)                           //如果时钟启动成功
	{
		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);                        //定义AHB设备时钟为系统时钟1分频
		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1);                         //定义APB2设备时钟为HCLK时钟1分频
		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);                         //定义APB1设备时钟为HCLK时钟2分频
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);                      //设定内部FLASH的的延时周期为2周期
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);   //使能FLASH预存取缓冲区
		/* PLLCLK = 8MHz * 3 = 24 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_3);    //配置PLL时钟为外部高速时钟的9倍频，8MHz * 9 = 72 MHz
		/* Enable PLL */
		RCC_PLLCmd(ENABLE);                                     //使能PLL时钟
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)      //等待PLL时钟设置完成准备就绪
		{
		}
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);              //使用PLL时钟作为系统时钟源
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)                    //返回系统所用时钟源确认为外部高速晶振，8M晶振。
		{
		}
	}
}

void GPIO_DI_NVIC_Configuration(uint32_t nvicGroup, uint8_t interuptNum)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 选择中断分组 */
  NVIC_PriorityGroupConfig(nvicGroup);				 //选择中断分组1（主优先级1位，从优先级3位）
  
  /* 配置外部中断0号线 */
  NVIC_InitStructure.NVIC_IRQChannel = interuptNum;	//选择外部中断0号线中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		 //主优先级为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			 //从优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //使能中断通道
  NVIC_Init(&NVIC_InitStructure);								 //用以上参数初始化0号线中断通道
}

void GPIO_DI_EXIT_Configuration(uint32_t EXTI_Line, uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  EXTI_InitTypeDef EXTI_InitStructure;
   /* 连接中断线路与按键所在的IO端口 */
  GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);	  //选择PA0作为外部中断线

  /* 配置PA0中断线 */    
  EXTI_InitStructure.EXTI_Line = EXTI_Line;					  //选择外部中断0号线
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			  //外部线路模式为中断模式
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		  //设置中断为下降沿有效
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;						  //打开中断线路

  EXTI_Init(&EXTI_InitStructure);								  //用以上参数初始化PA0所占中断线
}

void GPIO_DI_KEY0_Configration(void)
{
	/* Enable ,打开GPIO 时钟*/
	GPIO_InitTypeDef GPIO_InitStructure;

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //SWJ和JTAG失能
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	/* 配置中断 */
	GPIO_DI_NVIC_Configuration(NVIC_PriorityGroup_1, EXTI15_10_IRQn);

	GPIO_DI_EXIT_Configuration(EXTI_Line13, GPIO_PortSourceGPIOC, GPIO_PinSource13);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //端口模式为浮空输入方式
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSEConfig(RCC_LSE_OFF);
	BKP_TamperPinCmd(DISABLE);
	BKP_ITConfig(DISABLE);
	PWR_BackupAccessCmd(DISABLE);*/	
}

void GPIO_DI_KEY1_Configration(void)
{
	/* Enable ,打开GPIO 时钟*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);
	
	/* 配置中断 */
	GPIO_DI_NVIC_Configuration(NVIC_PriorityGroup_1, EXTI15_10_IRQn);

	GPIO_DI_EXIT_Configuration(EXTI_Line14, GPIO_PortSourceGPIOC, GPIO_PinSource14);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //端口模式为浮空输入方式
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void GPIO_DI_KEY2_Configration(void)
{
	/* Enable ,打开GPIO 时钟*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);
	
	/* 配置中断 */
	GPIO_DI_NVIC_Configuration(NVIC_PriorityGroup_1, EXTI15_10_IRQn);
	
	GPIO_DI_EXIT_Configuration(EXTI_Line15, GPIO_PortSourceGPIOC, GPIO_PinSource15);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //端口模式为浮空输入方式
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void GPIO_DO_REALY_Configration(void)
{
	/* Enable ,打开GPIO 时钟*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			  //时钟速度为50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //端口模式为浮空输入方式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void GPIO_DO_RS485_Configration(void)
{
	/* Enable ,打开GPIO 时钟*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			  //时钟速度为50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //端口模式为浮空输入方式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void GPIO_DO_LED_Configration(void)
{
	/* Enable ,打开GPIO 时钟*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			  //时钟速度为50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //端口模式为浮空输入方式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval : None
  */
void GPIO_Configuration(void)
{		

	GPIO_DI_KEY0_Configration();
	GPIO_DI_KEY1_Configration();
	GPIO_DI_KEY2_Configration();
	GPIO_DO_REALY_Configration();
	GPIO_DO_LED_Configration();
	GPIO_DO_RS485_Configration();
}

void ADC_Configuration()
{
	//V_IOUT_adcInit();
	//A24IN_adcInit();
	//ADC_IN_adcInit();	
	ADC_DMAS_adcInit();
}

void Flash_Configuration(uint8_t eraseFlag)
{
	__IO uint32_t StartAddr = 0x08040000;
	__IO uint32_t EndAddr = 0x0805AB38;
	uint32_t EraseCounter;
	__IO uint32_t NbrOfPage;
	volatile FLASH_Status FLASHStatus;
	FLASHStatus = FLASH_COMPLETE;
	/* Unlock the Flash Program Erase controller */
	FLASH_Unlock();
	/* Define the number of page to be erased */
	NbrOfPage = (EndAddr - StartAddr) / FLASH_PAGE_SIZE;
	/* Clear All pending flags */
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	if(eraseFlag == TRUE)
	{
		/* Erase the FLASH pages */
		for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
		{
			FLASHStatus = FLASH_ErasePage(StartAddr + (FLASH_PAGE_SIZE * EraseCounter));
		}
	}
}

void Timer_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 1;                 //自动装载
	TIM_TimeBaseStructure.TIM_Prescaler = 72;       //72M分频率到1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;  //向下计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
}

void SPIx_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;    
	/*允许 SPI2 和GPIOA时钟，这两个外设都是挂在APB2总线上的 */    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);       
	/*配置 SPI2 引脚，由于这里只用到了 SCK,和 MOSI ，所以只对PA5和PA7进行了初始化*/   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//关于这个参数的描述可以见GPIO的H文件   
	GPIO_Init(GPIOB, &GPIO_InitStructure);     /* 配置PA.4作为推挽输出，因为这里用来作为SPI口的片选，既选中LCD操作 */   
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_12;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_Init(GPIOB, &GPIO_InitStructure);     

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_Init(GPIOA, &GPIO_InitStructure);     
	
}

void SPIx_Configuration(void)
{
	SPI_InitTypeDef  SPI_InitStructure;   
	
	SPIx_GPIO_Config();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	/* 初始化片选为高，不选种LCD */   
	LCD_CS_SET;	//PA8;     
	/* SPI1 配置，关于这个怎么配置见STM32的手册*/    
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;   
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;   
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;   
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;    
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;   
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;   
	SPI_Init(SPI2, &SPI_InitStructure);        
	SPI_Cmd(SPI2, ENABLE);    
}

/**
  * @brief  Initialize the correspond device.
  * @param Device_Init: specifies the devices which will be initalized
  *   This parameter can be any combination of the following values:
  * @arg GPIO_INIT, RTC_INIT, USART_INIT, FLASH_INIT,
  *   FSCM_INIT, RCC_INIT
  * @retval : None
  */
void SystemResourcesInit(uint32_t Device_Init)
{
	if(Device_Init & RCC_INIT)
	{
		/* System Clocks Configuration */
		RCC_Configuration();
		//RCC_Internal_Configuration();
	}
	if(Device_Init & FSCM_INIT)
	{
		FSCM_Configuration();
	}
	if(Device_Init & FLASH_INIT)
	{
		Flash_Configuration(FALSE);
	}
	if(Device_Init & NVIC_INIT)
	{
		/* NVIC configuration */
		NVIC_Configuration();
	}
	if(Device_Init & GPIO_INIT)
	{
		/* Configure the GPIO */
		GPIO_Configuration();
	}
	if(Device_Init & USART_INIT)
	{
		/* Configure the USART */
		USARTx_Configuration();
	}
	if(Device_Init & SYSTICK_INIT)
	{
		/* SysTick Configuration */
		SysTick_Configuration();
	}
	if(Device_Init & TIMER_INIT)
	{
		/* Timer Configuration */
		Timer_Configuration();
	}
	if(Device_Init & SPI_INIT)
	{
		SPIx_Configuration();
	}
	if(Device_Init & DAC_INIT)
	{
		DAC_VOLTAGE_Configuration();
	}
	if(Device_Init & ADC_INIT)
	{
		ADC_Configuration();
	}
	
}
