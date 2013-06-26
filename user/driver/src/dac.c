#include "include.h"

void dacOutput(uint16_t value)
{
	DAC_SetChannel1Data(DAC_Align_12b_R, 0xffff - value);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET); 
}
