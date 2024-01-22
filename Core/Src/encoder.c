/*
 * encoder.c
 *
 *  Created on: Jan 22, 2024
 *      Author: sky.chu
 */

#include "encoder.h"
extern TIM_HandleTypeDef htim2;
uint16_t perviousEncdoerCounter = 0;

uint8_t btn() {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)) {
		return 1;
	} else {
		return 0;
	}
}

int encoder() {

	perviousEncdoerCounter = TIM2->CNT;
	if ( TIM2->CNT - perviousEncdoerCounter < 0) {
		return (-1);
	} else if (TIM2->CNT - perviousEncdoerCounter > 0) {
		return (1);
	}

	//reset encoder register
	if ( TIM2->CNT > 1023) {
		TIM2->CNT = 0;
		perviousEncdoerCounter = 0;
	}

	return (0);
}
