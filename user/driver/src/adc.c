#include "include.h"

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

uint16_t GetVINAdcValue(void)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	return ADC_GetConversionValue(ADC1);	//��ȡADC1ת������ֵ
}

uint16_t GetPowerAdcValue(void)
{
	
	return 4095;	//��ȡADC1ת������ֵ
}

