#include "NTCtempSensor.h"

//y=0.111x+264.262
//y=resistor x=temp

//const uint32_t ADC_CHANNEL[3] = { ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2 };
const double c1 = 0.7418740748e-3, c2 = 2.111100970e-4, c3 =1.190343927e-7;

void adcSelect(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel) {
	sConfig->Channel = channel;

}

//void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
//		NTC_TypeDef *uNTC) {
void calTemp(ADC_HandleTypeDef *hadc, NTC_TypeDef *uNTC, uint32_t inoputAdcValue[3]) {
//	getAdcVoltage(hadc, sConfig, uNTC);
	//calculating resistor value

//	for (int i = 1; i < 4; i++) {
//		//change ADC selection
//		adcSelect(hadc, &sConfig, ADC_CHANNEL[i]);
//		//get ADC value
//		uNTC->adcValue[i] = HAL_ADC_GetValue(hadc);
//		//cal resistor
//		float voltage = 0;
//		voltage = (uNTC->adcValue[i] / 4096.0) * 3.3; //2.38v 2.31
//		uNTC->logR2 = log(uNTC->resistor[i]);
//		uNTC->resistor[i] = (voltage * refenceResistor) / (supplyVoltage - voltage);
//
////		calculating temperature
//		uNTC->temp[i] = (1.0 / (c1 + c2* uNTC->logR2 + c3*(uNTC->logR2)*(uNTC->logR2)*uNTC->logR2));
////		uNTC->temp[i] = (uNTC->resistor[i] - 264.262) / 0.111;
	for(int i = 0; i < sizeof(inoputAdcValue[0] - 1); i++){
		uNTC->adcValue[i] = inoputAdcValue[i];
	}
		printf("run cal temp \r\n");
//		printf("size = %u\r\n", sizeof(inoputAdcValue[0]));
//		/*for average the adcvalue
		int simple = 10;
		int NumOfInoputAdc = sizeof(inoputAdcValue[0] - 1);
		uint32_t simpleArray[simple][NumOfInoputAdc];
//		*/
//		for (int i = 0; i < adcChannl; i++) {
		for (int i = 0; i < sizeof(inoputAdcValue[0] - 1); i++) {
//			/*for average the adcvalue


			for (int j = 0; j < simple; j++) {
				simpleArray[i][j] = uNTC->adcValue[i];
				printf("adcValue %d = ", i); //temp1 temp2 temp3
				printf("%lu\r\n", simpleArray[i][j]);
			}
//			 */

			//cal resistor
			float voltage = 0.0;
			voltage = (uNTC->adcValue[i] / 4096.0) * 3.3;
			uNTC->resistor[i] = (refenceResistor * 1.0 * voltage)/(supplyVoltage * 1.0 - (voltage));
			uNTC->logR2 = log(uNTC->resistor[i]);
			uNTC->temp[i] =(1.0 / (c1 + c2 * uNTC->logR2 + c3 * uNTC->logR2 * uNTC->logR2 * uNTC->logR2));

			printf("Temp %d =", i);
			uint32_t fti;
//				logR2 = logR2 *10000;
			fti = (uint32_t) uNTC->temp[i];
//				fti = (int) temp[i];
			printf("%lu\r\n", fti);
		}
}
