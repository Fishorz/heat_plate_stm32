/*
 * NTCtempSensor.h
 *
 *  Created on: Jan 22, 2024
 *      Author: sky.chu
 */

#ifndef INC_NTCTEMPSENSOR_H_
#define INC_NTCTEMPSENSOR_H_
#include "stm32f1xx_hal.h"
//#include "stm32f1xx_hal_adc.h"
#define supplyVoltage 3.3
#define refenceResistor 120 * 1000 //120k ohm
const float c1 = 0.7510226063e-03, c2 = 2.107052748e-04, c3 = 1.160934901e-07;

//const uint32_t ADC_CHANNEL[3] = { ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2 };

typedef struct {
	uint8_t adcValue[3];
	double temp[3];
	double resistor[3];
	double logR2;


} NTC_TypeDef;

void adcSelect(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel);
//void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
//		NTC_TypeDef *uNTC);
void calTemp(ADC_HandleTypeDef *hadc, NTC_TypeDef *uNTC);
#endif /* INC_NTCTEMPSENSOR_H_ */
