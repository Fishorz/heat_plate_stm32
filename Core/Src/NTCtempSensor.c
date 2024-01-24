#include "NTCtempSensor.h"
//extern ADC_HandleTypeDef hadc1;

//const float temperature_table [2][3] = {{25, 150, 250}, {103180, 1366.2, 168.6}};
//y=0.111x+264.262
//y=resistor x=temp



//extern ADC_HandleTypeDef hadc1;
//extern ADC_ChannelConfTypeDef sConfig;

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
		adcSelect(hadc, sConfig, ADC_CHANNE[i]);
		//get ADC value
		uNTC->adcValue[i] = HAL_ADC_GetValue(hadc);
		//cal resistor
		uNTC->resistor[i] = (uNTC->adcValue[0] * refenceResistor)
				/ (supplyVoltage - uNTC->adcValue[0]);

//		calculating temperature
		//y=0.111x+264.262
		//y=resistor x=temp
		uNTC->temp[i] = (uNTC->resistor[i] - 264.262) / 0.111;
	}
}
