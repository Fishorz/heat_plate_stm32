/*
 * MAX6675.c
 *
 *  Created on: Oct 16, 2024
 *      Author: ORZ
 */


/*************************************************************************************
 Title	 :  MAXIM Integrated MAX6675 Library for STM32 Using HAL Libraries
 Author  :  Bardia Alikhan Afshar <bardia.a.afshar@gmail.com>
 Software:  STM32CubeIDE
 Hardware:  Any STM32 device
*************************************************************************************/
#include"MAX6675.h"
#include"spi.h"
#include"gpio.h"
//SPI_HandleTypeDef hspi2;

// ------------------- Variables ----------------
_Bool TCF=0;                                          // Thermocouple Connection acknowledge Flag
uint8_t DATARX[2];                                    // Raw Data from MAX6675

// ------------------- Functions ----------------
float Max6675_Read_Temp(void){
float Temp=0;                                         // Temperature Variable
HAL_GPIO_WritePin(GPIOB,NSS_Pin,GPIO_PIN_RESET);       // Low State for SPI Communication
HAL_SPI_Receive(&hspi2,DATARX,1,50);                  // DATA Transfer
HAL_GPIO_WritePin(GPIOB,NSS_Pin,GPIO_PIN_SET);         // High State for SPI Communication
TCF=(((DATARX[0]|(DATARX[1]<<8))>>2)& 0x0001);        // State of Connecting
//if(TCF){
//	return -1;
//}
Temp=((((DATARX[0]|DATARX[1]<<8)))>>3);               // Temperature Data Extraction
Temp*=0.25;                                           // Data to Centigrade Conversation
HAL_Delay(250);                                       // Waits for Chip Ready(according to Datasheet, the max time for conversion is 220ms)
return Temp;
}
