/*
 * NTCtempSensor.h
 *
 *  Created on: Jan 22, 2024
 *      Author: sky.chu
 */

#ifndef INC_NTCTEMPSENSOR_H_
#define INC_NTCTEMPSENSOR_H_

#define supplyVoltage 3.3
#define refenceResistor 4.7 * 1000

#include "stm32f1xx_hal.h"

//const uint32_t ADC_CHANNEL[3] = { ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2 };

typedef struct {
	uint8_t adcValue[3];
	float temp[3];
	int resistor[3];

} NTC_TypeDef;

void adcSelect(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel);
void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		NTC_TypeDef *uNTC);
#endif /* INC_NTCTEMPSENSOR_H_ */
