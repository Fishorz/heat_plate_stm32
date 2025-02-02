/*
 * debug_print.h
 *
 *  Created on: 30 Jan 2024
 *      Author: sky.chu
 */

#ifndef INC_DEBUG_PRINT_H_
#define INC_DEBUG_PRINT_H_
#define DEBUG_PRINT 1

#include "stdio.h"
#include "stdlib.h"
#include "stm32f1xx_hal.h"


void debug_println(char msg[]);
//void debug_println(int msg);
void debug_print(char msg[]);
//void debug_print(int msg);
/*
		char Temp[10];
		itoa(counter, Temp, 10);
		debug_print("counter = ");
		debug_print(Temp);
		debug_print("\n\r");

*/
#endif /* INC_DEBUG_PRINT_H_ */
