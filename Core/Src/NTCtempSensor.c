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

void getAdcVoltage(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig) {

	adcSelect(hadc, sConfig, ADC_CHANNEL_0);
	adcValue0 = HAL_ADC_GetValue(hadc);

	adcSelect(hadc, sConfig, ADC_CHANNEL_1);
	adcValue1 = HAL_ADC_GetValue(hadc);

	adcSelect(hadc, sConfig, ADC_CHANNEL_2);
	adcValue2 = HAL_ADC_GetValue(hadc);
}

//Vadc = (NTC/(4.7k + ntc) ) *3.3
void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig) {
	getAdcVoltage(hadc, sConfig);
	//cal resistor value
//	int resistor1, resistor2, resistor3;
//	resistor1 = (adcValue0 * refenceResistor) / (supplyVoltage - )
}
