/*
 * NTCtempSensor.h
 *
 *  Created on: Jan 22, 2024
 *      Author: sky.chu
 */

#ifndef INC_NTCTEMPSENSOR_H_
#define INC_NTCTEMPSENSOR_H_

#include "stm32f1xx_hal.h"

void adcSelect(ADC_HandleTypeDef *hadc,
		ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel);
void getAdcVoltage(ADC_HandleTypeDef *hadc,
		ADC_ChannelConfTypeDef *sConfig);
void calTemp(ADC_HandleTypeDef *hadc,
		ADC_ChannelConfTypeDef *sConfig);

#endif /* INC_NTCTEMPSENSOR_H_ */
