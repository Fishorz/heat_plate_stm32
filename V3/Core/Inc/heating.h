/*
 * heating.h
 *
 *  Created on: Sep 15, 2024
 *      Author: ORZ
 */


#ifndef __HEATING_H__
#define __HEATING_H__


#include "main.h"
#include "heating.h"

#include "heating.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include <meun.h>

#define PID_KP 0.1
#define PID_KI 0.0
#define PID_KD 0.0
#define PID_DT 0.1

typedef struct {
	float temp;
	float uPid;
	float P, I, D;
	float error;
	float derivative ;
	float previousError;
	float integralError;
	float pwm_duty;

	float Kp;
	float Ki;
	float Kd;
	float dt;
}HEATING_TypeDef;

void init_pid(HEATING_TypeDef *heating);
void cal_pid(HEATING_TypeDef *heating, uint32_t nowTemp, uint32_t targetTemp);


#endif /*__ GPIO_H__ */
