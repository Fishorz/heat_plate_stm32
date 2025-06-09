/*
 * ErrorHandle.c
 *
 *  Created on: Nov 24, 2024
 *      Author: ORZ
 */

#include"ErrorHandler.h"

void errorHandlerInit(ERROR_TypeDef *error) {
	error->maxTemp = MAX_TEMP;
	error->minTemp = MIN_TEMP;
	error->targetTemp = 0;
//	error->errorOfTemp = ERROR_TEMP;
	error->errorState = normal;
	error->tempReached = 0;
	error->_tick = 0;
}

uint8_t tempReached(ERROR_TypeDef *error) {

	error->tempReached = (error->nowTemp > error->targetTemp - ERROR_TEMP && error->nowTemp < error->targetTemp + ERROR_TEMP) ? 1 : 0;
	return error->tempReached;
}

uint8_t overRange(ERROR_TypeDef *error) {
	if (error->nowTemp > error->maxTemp || error->nowTemp < error->minTemp)
		return 1;
	else
		return 0;
}

uint8_t increaseTempTimeOut(ERROR_TypeDef *error) {
	uint8_t timeOut = 0;
	tempReached(error);
	if (!error->tempReached && error->_tick > TIME_OUT ) {
		if (error->nowTemp < (error->tempBefore2Tick + ERROR_TEMP)) {
			timeOut = 1;
		}
	}
	if(error->_tick % 2 == 0){
		error->tempBefore2Tick = error->nowTemp;
	}
	return timeOut;
}

void errorHandler(ERROR_TypeDef *error, float nowTemp) {
	error->_tick++;
	if (overRange(error)) {
		error->errorState = tempOverRange;
	}
	if (increaseTempTimeOut(error)) {
		error->errorState = tempTimeOut;
	}
	//reset the tick
	if(error->_tick > TIME_OUT + 5){
		error->_tick = 0;
	}
}
