/*
 * encoder.c
 *
 *  Created on: Jan 22, 2024
 *      Author: sky.chu
 */

#include "encoder.h"
//extern TIM_HandleTypeDef htim2;
//uint16_t perviousEncdoerCounter = 0;
//
//uint8_t btn() {
//	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)) {
//		return 1;
//	} else {
//		return 0;
//	}
//}
//
//int encoder() {
//
//	perviousEncdoerCounter = TIM2->CNT;
//	if ( TIM2->CNT - perviousEncdoerCounter < 0) {
//		return (-1);
//	} else if (TIM2->CNT - perviousEncdoerCounter > 0) {
//		return (1);
//	}
//
//	//reset encoder register
//	if ( TIM2->CNT > 1023) {
//		TIM2->CNT = 0;
//		perviousEncdoerCounter = 0;
//	}
//
//	return (0);
//}

uint8_t pinA = 0;
uint8_t pinB = 0;
uint8_t state = 0;
int8_t encoderCounter = 0;
uint8_t _lastBtnState = 0;
uint8_t _btnState = 0;

void calculatEncoder() {
	pinA = (GPIOB->IDR & GPIO_PIN_7)>0;
	pinB = (GPIOB->IDR & GPIO_PIN_6)>0;

	state <<= 2; // if state = 0b0010 to 0b1000
	state |= (pinA << 1) | pinB; // previous state 0b1000 to 0b1011 (if a and b is 1)
	state &= 0x0F; //0x0F = 0b1111 (0d15)
	switch (state) {
	case (0b0001): //mean last state 00 and now is 01
	case (0b0111): //mean last state 01 and now is 11
	case (0b1110):
	case (0b1000):
		encoderCounter++;
		break;
	case (0b0010):
	case (0b1011):
	case (0b1101):
	case (0b0100):
		encoderCounter--;
		break;
	}
}

int btnState() {
	int _return = 0;
	_btnState = (GPIOB->IDR & GPIO_PIN_5)>0;
	if (_btnState == 1 && _lastBtnState == 0) {
		_return = 1;
	} else {
		_return = 0;
	}
	_lastBtnState = _btnState;
	return (_return);
}

int encoderState() {
	calculatEncoder();
	int _return;
	if (encoderCounter > 1) {
		_return = 1;
	} else if (encoderCounter < 1) {
		_return = -1;
	} else {
		_return = 0;
	}
	return (_return);
}
