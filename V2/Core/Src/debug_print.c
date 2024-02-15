/*
 * debug_print.c
 *
 *  Created on: 30 Jan 2024
 *      Author: sky.chu
 */
#include "debug_print.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
extern UART_HandleTypeDef huart1;

//debug-------------------------------------------
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 0xFFFF);

	return ch;
}
//debug-------------------------------------------

void debug_print(char msg[]) {
	if (DEBUG_PRINT == 1) {
		printf(msg);
		printf("\n\r");
	}
}

//void debug_print(int msg) {
//	if (DEBUG_PRINT == 1) {
//		printf(msg);
//		printf("/n/r");
//	}
//}

void debug_println(char msg[]) {
	if (DEBUG_PRINT == 1) {
		printf(msg);
	}
}

//void debug_println(int msg) {
//	if (DEBUG_PRINT == 1) {
//		printf(msg);;
//	}
//}
