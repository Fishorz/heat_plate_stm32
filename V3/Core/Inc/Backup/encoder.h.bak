/*
 * encoder.h
 *
 *  Created on: Jan 22, 2024
 *      Author: sky.chu
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f1xx_hal.h"

#define ENCODER_PIN_A (GPIOB->IDR & GPIO_PIN_7)
#define ENCODER_PIN_B (GPIOB->IDR & GPIO_PIN_6)
#define ENCODER_Btn (GPIOB->IDR & GPIO_PIN_5)

typedef struct{
	uint8_t pinA;
	uint8_t pinB;
	uint8_t pinBtn;
	uint8_t state;
	uint8_t encoderCounter;
	uint8_t lastEncoderCounter;
	uint8_t _lastBtnState;
	uint8_t _btnState;
}ENCODER_TypeDef;

//ENCODER_TypeDef encoder = {
//	.pinA;
//	.pinB;
//	.state;
//	.encoderCounter;
//	.lastBtnState;
//	.btnState;
//};

int btnState(ENCODER_TypeDef *encoder);
int encoderState(ENCODER_TypeDef *encoder);
//void calculatEncoder(ENCODER_TypeDef *encoder);

#endif /* INC_ENCODER_H_ */
