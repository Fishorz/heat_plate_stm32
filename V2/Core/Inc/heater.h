/*
 * hearter.h
 *
 *  Created on: Jan 19, 2024
 *      Author: sky.chu
 */

#ifndef INC_HEATER_H_
#define INC_HEATER_H_
#include "stm32f1xx_hal.h"
//user setpoint
#define SETPOINT 155
#include "PID.h"
#include "NTCtempSensor.h"
#define PID_KP  2.0f
#define PID_KI  0.5f
#define PID_KD  0.25f
#define PID_TAU 0.02f
#define PID_LIM_MIN 0.0f
#define PID_LIM_MAX  100.0f
#define PID_LIM_MIN_INT 0.0f
#define PID_LIM_MAX_INT  5.0f
#define SAMPLE_TIME_S 0.01f

typedef struct {
	uint8_t adcValue[3];
	float temp[3];
	int resistor[3];

	//pid
	double Input, Output, Setpoint;
	double errSum, lastErr;
	double kp, ki, kd;
	uint8_t timeChange;
} Heater_TypeDef;

void heaterInit(Heater_TypeDef *pid, double Kp, double Ki, double Kd, uint8_t TimeChange);
void Compute(Heater_TypeDef *pid);
void heating(ADC_HandleTypeDef *hadc, NTC_TypeDef *uNTC, int i);

#endif /* INC_HEATER_H_ */
