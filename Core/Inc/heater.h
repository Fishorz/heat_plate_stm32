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
#define PID_LIM_MIN -10.0f
#define PID_LIM_MAX  10.0f
#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT  5.0f
#define SAMPLE_TIME_S 0.01f

void heaterInit();
void heating();

#endif /* INC_HEATER_H_ */
