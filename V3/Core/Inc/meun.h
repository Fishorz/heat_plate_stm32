#ifndef __MEUN_H_
#define __MEUN_H_

#include "liquidcrystal_i2c.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "encoder.h"



typedef struct  {   // Structure declaration
//	uint8_t meunIndex;
//	uint8_t meunLayer;
//	uint8_t previousMeunIndex;
	uint8_t meunNeedUpdate; //is the meun need to update?

	int32_t nowTemp;
	int16_t targetTemp;
	uint8_t state; 			//is heating or standby
	char status[8];			//for lcd transmit char

	//for display meun state
	enum display_item{
		welcome,
		Standby,
		Heating
	}ITEM_Enum;


	enum display_item meunIndex;
	enum display_item lastIndex;

}MEUN_TypeDef;

void meunInit(MEUN_TypeDef *meun, int defaultTemp);

void updateDisplay(MEUN_TypeDef *meun);

void startScreeen(MEUN_TypeDef *meun);
void displayMeunHandler(MEUN_TypeDef *meun);
void selectMeunHandler(MEUN_TypeDef *meun, ENCODER_TypeDef *encoder);

void standby_page(MEUN_TypeDef *meun);

void first_page();
void second_page();
void third_page();

// End the structure with a semicolon

#endif //__MEUN_H_
