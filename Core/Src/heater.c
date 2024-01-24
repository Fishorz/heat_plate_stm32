/*
 * heater.c
 *
 *  Created on: Jan 19, 2024
 *      Author: sky.chu
 */

#include "heater.h"
#define TEMP_SET_POINT 50.1
extern double currentTemp, PIDOut, TempSetpoint;

float GetTemp(void) {

	/*
	 * Temperature simulink by ratio of PIDOut
	 */

	static float tmp = 0;

	tmp += (PIDOut / 100);

	return tmp;
}

void calculatePID() {
	currentTemp = GetTemp();
//	PID_Compute(&TPID);

	//sprintf(msg, "Temperature: %3.2f /PID Value: %d\r\n", Temp,(int16_t) PIDOut);
	//HAL_UART_Transmit(&huart1, (uint8_t*) msg, strlen(msg), 100);
}
