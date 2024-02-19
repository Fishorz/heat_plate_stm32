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

//void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
//		NTC_TypeDef *uNTC) {
void calTemp(ADC_HandleTypeDef *hadc, NTC_TypeDef *uNTC) {
//	getAdcVoltage(hadc, sConfig, uNTC);
	//calculating resistor value
	ADC_ChannelConfTypeDef sConfig = { 0 };

	for (int i = 1; i < 4; i++) {
		//change ADC selection
		adcSelect(hadc, &sConfig, ADC_CHANNEL[i]);
		//get ADC value
		uNTC->adcValue[i] = HAL_ADC_GetValue(hadc);
		//cal resistor
		float voltage = 0;
		voltage = (uNTC->adcValue[i] / 4096.0) * 3.3; //2.38v 2.31
		uNTC->logR2 = log(uNTC->resistor[i]);
		uNTC->resistor[i] = (voltage * refenceResistor) / (supplyVoltage - voltage);

//		calculating temperature
		uNTC->temp[i] = (1.0 / (c1 + c2* uNTC->logR2 + c3*(uNTC->logR2)*(uNTC->logR2)*uNTC->logR2));
//		uNTC->temp[i] = (uNTC->resistor[i] - 264.262) / 0.111;
	}
}
