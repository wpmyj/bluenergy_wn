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

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //ʱ���ٶ�Ϊ50M
	/* USART Configuration  */
	/*����USART2(����2)����IO��*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                   //���ͽ�ΪPA9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);                      //�����ϼ���������ʼ��PA��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                  //���ս�ΪPA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //���ÿ�©����
	GPIO_Init(GPIOA, &GPIO_InitStructure);                      //�����ϼ���������ʼ��PA��
}

/**
  * @brief  Configures the USART.
  * @param  None
  * @retval : None
  */
void USARTx_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	/* (1) ---- Enable USART2, GPIOA, �򿪴���2 ��GPIOAʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	/* (2) ----  ����USART1�ж�*/
	USARTx_NVIC_Init();
	/* (3) ---- ����USART1(����1)����IO��*/
	USART_GPIO_Init();
	/* (4) ---- USART
	  - USART2 configured as follow:
	  - ������ = 115200 baud
	  - �ֳ� = 8 Bits
	  - һ��ֹͣλ
	  - ��У��λ
	  - �ر����������� (RTS and CTS signals)
	*/
	USART_InitStructure.USART_BaudRate = 9600;                   //���ô��ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;    //�������ݳ���Ϊ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;         //����һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;           //��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//��ֹӲ��������ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�򿪴��ڵ��շ�����
	/* ����USART2 */
	USART_Init(USART2, &USART_InitStructure);                      //�����ϲ�����ʼ��USART2
	/* ���ô���1�����ж� */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                 //�򿪽����ж�
	/*ʹ�ܴ���2 */
	USART_Cmd(USART2, ENABLE);                                     //�򿪴���2
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
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //ʱ���ٶ�Ϊ50M
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
	/*����FSCM����IO��*/
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

	//������ RCC�Ĵ�������Ϊȱʡֵ

	RCC_DeInit();

	RCC_HSICmd(ENABLE);

	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	if(HSEStartUpStatus == SUCCESS) 
	{

		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		RCC_PCLK2Config(RCC_HCLK_Div1);

		RCC_PCLK1Config(RCC_HCLK_Div2);

		//���� PLL ʱ��Դ����Ƶϵ��

		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_2);

		//ʹ�ܻ���ʧ�� PLL,�����������ȡ��ENABLE����DISABLE

		RCC_PLLCmd(ENABLE);//���PLL������ϵͳʱ��,��ô�����ܱ�ʧ��

		//�ȴ�ָ���� RCC ��־λ���óɹ� �ȴ�PLL��ʼ���ɹ�

		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		//����ϵͳʱ�ӣ�SYSCLK�� ����PLLΪϵͳʱ��Դ

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		//�ȴ�PLL�ɹ�������ϵͳʱ�ӵ�ʱ��Դ

		// 0x00��HSI ��Ϊϵͳʱ��

		// 0x04��HSE��Ϊϵͳʱ��

		// 0x08��PLL��Ϊϵͳʱ��

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
	RCC_DeInit();                                             //ʱ�ӿ��ƼĴ���ȫ���ָ�Ĭ��ֵ
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);                                //�ⲿ����ʱ��Դ������8M����
	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();               //�ȴ��ⲿʱ�Ӿ���
	if(HSEStartUpStatus == SUCCESS)                           //���ʱ�������ɹ�
	{
		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);                        //����AHB�豸ʱ��Ϊϵͳʱ��1��Ƶ
		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1);                         //����APB2�豸ʱ��ΪHCLKʱ��1��Ƶ
		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);                         //����APB1�豸ʱ��ΪHCLKʱ��2��Ƶ
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);                      //�趨�ڲ�FLASH�ĵ���ʱ����Ϊ2����
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);   //ʹ��FLASHԤ��ȡ������
		/* PLLCLK = 8MHz * 3 = 24 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_3);    //����PLLʱ��Ϊ�ⲿ����ʱ�ӵ�9��Ƶ��8MHz * 9 = 72 MHz
		/* Enable PLL */
		RCC_PLLCmd(ENABLE);                                     //ʹ��PLLʱ��
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)      //�ȴ�PLLʱ���������׼������
		{
		}
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);              //ʹ��PLLʱ����Ϊϵͳʱ��Դ
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)                    //����ϵͳ����ʱ��Դȷ��Ϊ�ⲿ���پ���8M����
		{
		}
	}
}

void GPIO_DI_NVIC_Configuration(uint32_t nvicGroup, uint8_t interuptNum)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ѡ���жϷ��� */
  NVIC_PriorityGroupConfig(nvicGroup);				 //ѡ���жϷ���1�������ȼ�1λ�������ȼ�3λ��
  
  /* �����ⲿ�ж�0���� */
  NVIC_InitStructure.NVIC_IRQChannel = interuptNum;	//ѡ���ⲿ�ж�0�����ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		 //�����ȼ�Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			 //�����ȼ�Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //ʹ���ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);								 //�����ϲ�����ʼ��0�����ж�ͨ��
}

void GPIO_DI_EXIT_Configuration(uint32_t EXTI_Line, uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  EXTI_InitTypeDef EXTI_InitStructure;
   /* �����ж���·�밴�����ڵ�IO�˿� */
  GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);	  //ѡ��PA0��Ϊ�ⲿ�ж���

  /* ����PA0�ж��� */    
  EXTI_InitStructure.EXTI_Line = EXTI_Line;					  //ѡ���ⲿ�ж�0����
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			  //�ⲿ��·ģʽΪ�ж�ģʽ
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		  //�����ж�Ϊ�½�����Ч
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;						  //���ж���·

  EXTI_Init(&EXTI_InitStructure);								  //�����ϲ�����ʼ��PA0��ռ�ж���
}

void GPIO_DI_KEY0_Configration(void)
{
	/* Enable ,��GPIO ʱ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //SWJ��JTAGʧ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	/* �����ж� */
	GPIO_DI_NVIC_Configuration(NVIC_PriorityGroup_1, EXTI15_10_IRQn);

	GPIO_DI_EXIT_Configuration(EXTI_Line13, GPIO_PortSourceGPIOC, GPIO_PinSource13);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //�˿�ģʽΪ�������뷽ʽ
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
	/* Enable ,��GPIO ʱ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);
	
	/* �����ж� */
	GPIO_DI_NVIC_Configuration(NVIC_PriorityGroup_1, EXTI15_10_IRQn);

	GPIO_DI_EXIT_Configuration(EXTI_Line14, GPIO_PortSourceGPIOC, GPIO_PinSource14);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //�˿�ģʽΪ�������뷽ʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void GPIO_DI_KEY2_Configration(void)
{
	/* Enable ,��GPIO ʱ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);
	
	/* �����ж� */
	GPIO_DI_NVIC_Configuration(NVIC_PriorityGroup_1, EXTI15_10_IRQn);
	
	GPIO_DI_EXIT_Configuration(EXTI_Line15, GPIO_PortSourceGPIOC, GPIO_PinSource15);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //�˿�ģʽΪ�������뷽ʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void GPIO_DO_REALY_Configration(void)
{
	/* Enable ,��GPIO ʱ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			  //ʱ���ٶ�Ϊ50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //�˿�ģʽΪ�������뷽ʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void GPIO_DO_RS485_Configration(void)
{
	/* Enable ,��GPIO ʱ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			  //ʱ���ٶ�Ϊ50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //�˿�ģʽΪ�������뷽ʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void GPIO_DO_LED_Configration(void)
{
	/* Enable ,��GPIO ʱ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			  //ʱ���ٶ�Ϊ50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //�˿�ģʽΪ�������뷽ʽ
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

	TIM_TimeBaseStructure.TIM_Period = 1;                 //�Զ�װ��
	TIM_TimeBaseStructure.TIM_Prescaler = 72;       //72M��Ƶ�ʵ�1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;  //���¼���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
}

void SPIx_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;    
	/*���� SPI2 ��GPIOAʱ�ӣ����������趼�ǹ���APB2�����ϵ� */    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);       
	/*���� SPI2 ���ţ���������ֻ�õ��� SCK,�� MOSI ������ֻ��PA5��PA7�����˳�ʼ��*/   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//��������������������Լ�GPIO��H�ļ�   
	GPIO_Init(GPIOB, &GPIO_InitStructure);     /* ����PA.4��Ϊ�����������Ϊ����������ΪSPI�ڵ�Ƭѡ����ѡ��LCD���� */   
	
	
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

	/* ��ʼ��ƬѡΪ�ߣ���ѡ��LCD */   
	LCD_CS_SET;	//PA8;     
	/* SPI1 ���ã����������ô���ü�STM32���ֲ�*/    
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
