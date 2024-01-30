/*
 * heater.c
 *
 *  Created on: Jan 19, 2024
 *      Author: sky.chu
 */

#include "heater.h"
uint16_t setpoint = SETPOINT;

PIDController pid = { PID_KP, PID_KI, PID_KD,
PID_TAU,
PID_LIM_MIN, PID_LIM_MAX,
PID_LIM_MIN_INT, PID_LIM_MAX_INT,
SAMPLE_TIME_S };

NTC_TypeDef ntc1;
extern ADC_HandleTypeDef hadc1;
ADC_ChannelConfTypeDef heaterADC;

void heaterInit() {
	PIDController_Init(&pid);
}

void heating() {
	/* Compute new control signal */
	calTemp(&hadc1, &heaterADC, &ntc1);
	PIDController_Update(&pid, setpoint, ntc1.temp[0]);

}
