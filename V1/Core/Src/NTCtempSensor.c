#include "NTCtempSensor.h"

//y=0.111x+264.262
//y=resistor x=temp

const uint32_t ADC_CHANNEL[3] = { ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2 };

void adcSelect(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel) {
	sConfig->Channel = channel;
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, 100);
}

void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		NTC_TypeDef *uNTC) {
//	getAdcVoltage(hadc, sConfig, uNTC);
	//calculating resistor value

	for (int i = 0; i < 3; i++) {
		//change ADC selection
		adcSelect(hadc, sConfig, ADC_CHANNEL[i]);
		//get ADC value
		uNTC->adcValue[i] = HAL_ADC_GetValue(hadc);
		//cal resistor
		uNTC->resistor[i] = (uNTC->adcValue[0] * refenceResistor) / (supplyVoltage - uNTC->adcValue[0]);

//		calculating temperature
		//y=0.111x+264.262
		//y=resistor x=temp
		uNTC->temp[i] = (uNTC->resistor[i] - 264.262) / 0.111;
	}
}
