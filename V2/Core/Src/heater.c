/*
 * heater.c
 *
 *  Created on: Jan 19, 2024
 *      Author: sky.chu
 */

#include "heater.h"

uint16_t setpoint = SETPOINT;

//NTC_TypeDef ntc1;
//extern ADC_HandleTypeDef hadc1;
//ADC_ChannelConfTypeDef heaterADC;

void heaterInit(PIDController *pid) {
	PIDController_Init(pid);
}

void heating(ADC_HandleTypeDef *hadc, NTC_TypeDef *uNTC, PIDController *pid, int i) {
	/* Compute new control signal */
	calTemp(hadc, uNTC);
	float temp = 0;
	temp = uNTC->temp[i];
	PIDController_Update(pid, setpoint, temp);
}
