#include "include.h"

void DAC_RCC_Init(void)
{
	DAC_DeInit();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);		   //使能由APB1时钟控制的外设中的DAC端口
}

void DAC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	
	/*DAC通道IO配置*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;				//IO端口的第4位
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为输出(模拟输入方式不行)
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//用以上几个参数初始化PA口
}

void DAC_Channel_Init(void)
{
	DAC_InitTypeDef	DAC_InitStructure;	
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;      
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
}

void DAC_VOLTAGE_Configuration(void)
{
	DAC_RCC_Init();
	DAC_GPIO_Init();
	DAC_Channel_Init();	
}

void DacOutput(uint16_t value)
{
	DAC_SetChannel1Data(DAC_Align_12b_R, value);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET); 
}

