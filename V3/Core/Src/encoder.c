/*
 * encoder.c
 *
 *  Created on: Jan 22, 2024
 *      Author: sky.chu
 */

#include "encoder.h"
#include "main.h"

//ENCODER_TypeDef encoder = {
//	.pinA = ENCODER_PIN_A,
//	.pinB = ENCODER_PIN_B,
//	.pinBtn = ENCODER_Btn,
//	.state = 0,
//	.encoderCounter = 0,
//	._lastBtnState = 0,
//	._btnState = 0,
//};

//void encoderInt(ENCODER_TypeDef *encoder) {
//	encoder->state = 0;
//	encoder->encoderCounter = 0;
//	encoder->_lastBtnState = 0;
//	encoder->_btnState = 0;
//}

//void calculatEncoder(ENCODER_TypeDef *encoder) {
//	encoder->pinA = ENCODER_PIN_A > 0;
//	encoder->pinB = ENCODER_PIN_B > 0;
//
//	encoder->state <<= 2; // if state = 0b0010 to 0b1000
//	switch (encoder->state) {
//	case (0b0001): //mean last state 00 and now is 01
//	case (0b0111): //mean last state 01 and now is 11
//	case (0b1110):
//	case (0b1000):
//		encoder->encoderCounter++;
//		break;
//	case (0b0010):
//	case (0b1011):
//	case (0b1101):
//	case (0b0100):
//		encoder->encoderCounter--;
//		break;
//	}
//}

int btnState(ENCODER_TypeDef *encoder) {

	int _return = 0;
	encoder->_btnState = ENCODER_Btn > 0;
//	HAL_Delay(50);
	if (encoder->_btnState == 1 && encoder->_lastBtnState == 0) {
		_return = 1;
	} else {
		_return = 0;
	}
	encoder->_lastBtnState = encoder->_btnState;
	return (_return);
}

int encoderState(ENCODER_TypeDef *encoder) {
//	calculatEncoder(encoder);
	encoder->encoderCounter = (TIM4->CNT) >> 2;
//	int _return;
	if (encoder->encoderCounter != encoder->lastEncoderCounter) {
		if (encoder->encoderCounter - encoder->lastEncoderCounter > 0) {
			encoder->lastEncoderCounter = encoder->encoderCounter;
			return 1;
		} else if (encoder->encoderCounter - encoder->lastEncoderCounter < 0) {
			encoder->lastEncoderCounter = encoder->encoderCounter;

			return -1;
		}
	}
	return (0);
}
