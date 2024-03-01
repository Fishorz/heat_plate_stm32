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

void heating( NTC_TypeDef *uNTC, int i,uint32_t inoputAdcValue[3]) {
	/* Compute new control signal */
	calTemp(uNTC, inoputAdcValue);
//	float temp = 0;
//	temp = uNTC->temp[i];
}

void heaterInit(Heater_TypeDef *pid, double Kp, double Ki, double Kd,
		uint8_t TimeChange) {
	pid->kp = Kp;
	pid->ki = Ki;
	pid->kd = Kd;
	pid->timeChange = TimeChange;
}

void Compute(Heater_TypeDef *pid) {
	/*How long since we last calculated*/

	/*Compute all the working error variables*/
	double error = pid->Setpoint - pid->Input;
	pid->errSum += (error * pid->timeChange);
	double dErr = (error - pid->lastErr) / pid->timeChange;

	/*Compute PID Output*/
	pid->Output = pid->kp * error + pid->ki * pid->errSum + pid->kd * dErr;

	/*Remember some variables for next time*/
	pid->lastErr = error;
}
