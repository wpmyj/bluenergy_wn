#include "include.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

__IO uint16_t ADCConvertedValue[3];


void V_IOUT_adcInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

	/*����PC0 (ADC Channel10) Ϊģ������ -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		  //IO�˿ڵĵ�0λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	  //�˿�ģʽΪģ�����뷽ʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);		  //�����ϼ���������ʼ��PC��

	/* ADC1 ģ����ת������ ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	 //ADC1��ADC2�����Ķ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			 //ADC����Ϊ��ͨ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	 //����Ϊ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //��������ƿ�ʼת�������д���ʽ�ȣ�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   //AD�����ֵΪ�Ҷ˶��뷽ʽ
	ADC_InitStructure.ADC_NbrOfChannel = 1;					   //ָ��Ҫ����ADת�����ŵ�1
	ADC_Init(ADC1, &ADC_InitStructure);						   //������Ĳ�����ʼ��ADC1

	//��ADC1�ŵ�1��ת��ͨ��10��PC0���Ĳ���ʱ������Ϊ55.5������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);                                 //ʹ��ADC1
	ADC_ResetCalibration(ADC1);							 //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));			 //�õ�����У׼�Ĵ���״̬
	ADC_StartCalibration(ADC1);							 //��ʼУ׼ADC1
	while(ADC_GetCalibrationStatus(ADC1));				 //�õ�У׼�Ĵ���״̬
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 //ʹ��ADC1��������ƿ�ʼת��
}

void A24IN_adcInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

	/*����PC0 (ADC Channel10) Ϊģ������ -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		  //IO�˿ڵĵ�0λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	  //�˿�ģʽΪģ�����뷽ʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);		  //�����ϼ���������ʼ��PC��

	/* ADC1 ģ����ת������ ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	 //ADC1��ADC2�����Ķ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			 //ADC����Ϊ��ͨ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	 //����Ϊ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //��������ƿ�ʼת�������д���ʽ�ȣ�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   //AD�����ֵΪ�Ҷ˶��뷽ʽ
	ADC_InitStructure.ADC_NbrOfChannel = 1;					   //ָ��Ҫ����ADת�����ŵ�1
	ADC_Init(ADC1, &ADC_InitStructure);						   //������Ĳ�����ʼ��ADC1

	//��ADC1�ŵ�1��ת��ͨ��10��PC0���Ĳ���ʱ������Ϊ55.5������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);                                 //ʹ��ADC1
	ADC_ResetCalibration(ADC1);							 //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));			 //�õ�����У׼�Ĵ���״̬
	ADC_StartCalibration(ADC1);							 //��ʼУ׼ADC1
	while(ADC_GetCalibrationStatus(ADC1));				 //�õ�У׼�Ĵ���״̬
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 //ʹ��ADC1��������ƿ�ʼת��
}

void ADC_IN_adcInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);

	/*����PC0 (ADC Channel10) Ϊģ������ -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		  //IO�˿ڵĵ�0λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	  //�˿�ģʽΪģ�����뷽ʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);		  //�����ϼ���������ʼ��PC��

	/* ADC1 ģ����ת������ ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	 //ADC1��ADC2�����Ķ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			 //ADC����Ϊ��ͨ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	 //����Ϊ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //��������ƿ�ʼת�������д���ʽ�ȣ�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   //AD�����ֵΪ�Ҷ˶��뷽ʽ
	ADC_InitStructure.ADC_NbrOfChannel = 1;					   //ָ��Ҫ����ADת�����ŵ�1
	ADC_Init(ADC1, &ADC_InitStructure);						   //������Ĳ�����ʼ��ADC1

	//��ADC1�ŵ�1��ת��ͨ��10��PC0���Ĳ���ʱ������Ϊ55.5������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);                                 //ʹ��ADC1
	ADC_ResetCalibration(ADC1);							 //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));			 //�õ�����У׼�Ĵ���״̬
	ADC_StartCalibration(ADC1);							 //��ʼУ׼ADC1
	while(ADC_GetCalibrationStatus(ADC1));				 //�õ�У׼�Ĵ���״̬
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 //ʹ��ADC1��������ƿ�ʼת��
}

void ADC_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
}

void ADC_DMAS_adcInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);

	ADC_DMA_Init();

	/*����PC0 (ADC Channel10) Ϊģ������ -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;		  //IO�˿ڵĵ�0λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	  //�˿�ģʽΪģ�����뷽ʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);		  //�����ϼ���������ʼ��PC��

	
	/*����PC0 (ADC Channel10) Ϊģ������ -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		  //IO�˿ڵĵ�0λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	  //�˿�ģʽΪģ�����뷽ʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);		  //�����ϼ���������ʼ��PC��

	/* ADC1 ģ����ת������ ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	 //ADC1��ADC2�����Ķ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;			 //ADC����Ϊ��ͨ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	 //����Ϊ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //��������ƿ�ʼת�������д���ʽ�ȣ�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   //AD�����ֵΪ�Ҷ˶��뷽ʽ
	ADC_InitStructure.ADC_NbrOfChannel = 3;					   //ָ��Ҫ����ADת�����ŵ�1
	ADC_Init(ADC1, &ADC_InitStructure);						   //������Ĳ�����ʼ��ADC1

	//��ADC1�ŵ�1��ת��ͨ��10��PC0���Ĳ���ʱ������Ϊ55.5������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 3, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);                                 //ʹ��ADC1
	ADC_ResetCalibration(ADC1);							 //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));			 //�õ�����У׼�Ĵ���״̬
	ADC_StartCalibration(ADC1);							 //��ʼУ׼ADC1
	while(ADC_GetCalibrationStatus(ADC1));				 //�õ�У׼�Ĵ���״̬
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 //ʹ��ADC1��������ƿ�ʼת��
}


uint16_t GetVINAdcValue(void)
{
	return ADCConvertedValue[2];	//��ȡADC1ת������ֵ
}

uint16_t GetPowerAdcValue(void)
{
	
	return ADCConvertedValue[1];	//��ȡADC1ת������ֵ
}

