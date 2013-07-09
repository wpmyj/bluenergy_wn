#include "include.h"

void V_IOUT_adcInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

	/*配置PC0 (ADC Channel10) 为模拟输入 -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		  //IO端口的第0位
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	  //端口模式为模拟输入方式
	GPIO_Init(GPIOA, &GPIO_InitStructure);		  //用以上几个参数初始化PC口

	/* ADC1 模数器转换配置 ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	 //ADC1和ADC2工作的独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			 //ADC设置为多通道扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	 //设置为连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //由软件控制开始转换（还有触方式等）
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   //AD输出数值为右端对齐方式
	ADC_InitStructure.ADC_NbrOfChannel = 1;					   //指定要进行AD转换的信道1
	ADC_Init(ADC1, &ADC_InitStructure);						   //用上面的参数初始化ADC1

	//将ADC1信道1的转换通道10（PC0）的采样时间设置为55.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);                                 //使能ADC1
	ADC_ResetCalibration(ADC1);							 //重置ADC1校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));			 //得到重置校准寄存器状态
	ADC_StartCalibration(ADC1);							 //开始校准ADC1
	while(ADC_GetCalibrationStatus(ADC1));				 //得到校准寄存器状态
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 //使能ADC1由软件控制开始转换
}

void A24IN_adcInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

	/*配置PC0 (ADC Channel10) 为模拟输入 -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		  //IO端口的第0位
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	  //端口模式为模拟输入方式
	GPIO_Init(GPIOA, &GPIO_InitStructure);		  //用以上几个参数初始化PC口

	/* ADC1 模数器转换配置 ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	 //ADC1和ADC2工作的独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			 //ADC设置为多通道扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	 //设置为连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //由软件控制开始转换（还有触方式等）
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   //AD输出数值为右端对齐方式
	ADC_InitStructure.ADC_NbrOfChannel = 1;					   //指定要进行AD转换的信道1
	ADC_Init(ADC1, &ADC_InitStructure);						   //用上面的参数初始化ADC1

	//将ADC1信道1的转换通道10（PC0）的采样时间设置为55.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);                                 //使能ADC1
	ADC_ResetCalibration(ADC1);							 //重置ADC1校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));			 //得到重置校准寄存器状态
	ADC_StartCalibration(ADC1);							 //开始校准ADC1
	while(ADC_GetCalibrationStatus(ADC1));				 //得到校准寄存器状态
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 //使能ADC1由软件控制开始转换
}


void ADC_IN_adcInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);

	/*配置PC0 (ADC Channel10) 为模拟输入 -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		  //IO端口的第0位
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	  //端口模式为模拟输入方式
	GPIO_Init(GPIOB, &GPIO_InitStructure);		  //用以上几个参数初始化PC口

	/* ADC1 模数器转换配置 ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	 //ADC1和ADC2工作的独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			 //ADC设置为多通道扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	 //设置为连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //由软件控制开始转换（还有触方式等）
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   //AD输出数值为右端对齐方式
	ADC_InitStructure.ADC_NbrOfChannel = 1;					   //指定要进行AD转换的信道1
	ADC_Init(ADC1, &ADC_InitStructure);						   //用上面的参数初始化ADC1

	//将ADC1信道1的转换通道10（PC0）的采样时间设置为55.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);                                 //使能ADC1
	ADC_ResetCalibration(ADC1);							 //重置ADC1校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));			 //得到重置校准寄存器状态
	ADC_StartCalibration(ADC1);							 //开始校准ADC1
	while(ADC_GetCalibrationStatus(ADC1));				 //得到校准寄存器状态
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 //使能ADC1由软件控制开始转换
}

uint16_t GetVINAdcValue(void)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	return ADC_GetConversionValue(ADC1);	//读取ADC1转换出的值
}

uint16_t GetPowerAdcValue(void)
{
	
	return 4095;	//读取ADC1转换出的值
}

