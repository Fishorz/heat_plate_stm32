/*
 * ErrorHandler.h
 *
 *  Created on: Nov 24, 2024
 *      Author: ORZ
 */

#ifndef INC_ERRORHANDLER_H_
#define INC_ERRORHANDLER_H_

#include "main.h"
#include "config.h"
/*
 * Error type:
 * increasing temperature time out: temperature should be rise XX degree in XX(ms) time, if not cause this error
 * temperature over range: there is Max and Min temperature, if over the range cause this error
 * */

#endif /* INC_ERRORHANDLER_H_ */


typedef struct  {   // Structure declaration

	int16_t maxTemp;
	int16_t minTemp;

	uint8_t TimeOutIsActivate;
	int16_t errorOfTemp; //how much error mean reach the targetTemp and don't activated
	int32_t nowTemp;
	int32_t tempBefore2Tick;
	int32_t targetTemp;
	uint32_t _tick;
	uint8_t errorState;
	uint8_t tempReached;


	//for display meun state
	enum error_item{
		normal,
		tempTimeOut,
		tempOverRange
	}ERROR_Enum;

}ERROR_TypeDef;

void errorHandlerInit(ERROR_TypeDef *error);
void  errorHandler(ERROR_TypeDef *error, float nowTemp);

uint8_t increaseTempTimeOut(ERROR_TypeDef *error);
uint8_t overRange(ERROR_TypeDef *error);
uint8_t tempReached(ERROR_TypeDef *error);
