#include "NTCtempSensor.h"

//y=0.111x+264.262
//y=resistor x=temp

//const uint32_t ADC_CHANNEL[3] = { ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2 };
const double c1 = 0.7418740748e-3, c2 = 2.111100970e-4, c3 = 1.190343927e-7;

void adcSelect(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel) {
	sConfig->Channel = channel;

}

//void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
//		NTC_TypeDef *uNTC) {
float calTemp(ADC_HandleTypeDef *hadc, NTC_TypeDef *uNTC, uint32_t inoputAdcValue) {
	uNTC->adcValue = inoputAdcValue;
	printf("run cal temp \r\n");

	//cal resistor
	float voltage = 0.0;
	voltage = (uNTC->adcValue / 4096.0) * 3.3;
	uNTC->resistor = (refenceResistor * 1.0 * voltage)
			/ (supplyVoltage * 1.0 - (voltage));
	uNTC->logR2 = log(uNTC->resistor);
	uNTC->temp = (1.0 / (c1 + c2 * uNTC->logR2 + c3 * uNTC->logR2 * uNTC->logR2 * uNTC->logR2));

	uint32_t fti; //double to int
//				logR2 = logR2 *10000;
	fti = (uint32_t) uNTC->temp;
//				fti = (int) temp[i];
	printf("run cal temp done!!\r\n");
	return uNTC->temp;
}
