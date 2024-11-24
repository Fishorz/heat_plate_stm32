/*
 * ErrorHandle.c
 *
 *  Created on: Nov 24, 2024
 *      Author: ORZ
 */

#include"ErrorHandler.h"

void ErrorHandlerInit(ERROR_TypeDef *error) {
	error->maxTemp = MAX_TEMP;
	error->minTemp = MIN_TEMP;
	error->errorOfTemp = ERROR_TEMP;
	error->errorState = normal;

}

uint8_t checkOverRange(ERROR_TypeDef *error) {
	if (error->nowTemp > error->maxTemp || error->nowTemp < error->minTemp)
		return 1;
	else
		return 0;
}

void  ErrorHandler(ERROR_TypeDef *error, float nowTemp, uint32_t counter){

	if(checkOverRange(error)){
		error->errorState = tempOverRange;
	};
}
