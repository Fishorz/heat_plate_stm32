/*
 * NTCtempSensor.h
 *
 *  Created on: Jan 22, 2024
 *      Author: sky.chu
 */

#ifndef INC_NTCTEMPSENSOR_H_
#define INC_NTCTEMPSENSOR_H_
#include "stm32f1xx_hal.h"
#include <math.h>
#include <stdio.h>
//#include "stm32f1xx_hal_adc.h"
#define supplyVoltage 5.0
#define refenceResistor 120 * 1000 //120k ohm

//const uint32_t ADC_CHANNEL[3] = { ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2 };

typedef struct {
	uint32_t adcValue;
	double temp;
	double resistor;
	double logR2;

} NTC_TypeDef;

void adcSelect(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel);
float calTemp(ADC_HandleTypeDef *hadc, NTC_TypeDef *uNTC, uint32_t inoputAdcValue);
#endif /* INC_NTCTEMPSENSOR_H_ */
