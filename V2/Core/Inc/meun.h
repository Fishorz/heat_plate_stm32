#ifndef __MEUN_H_
#define __MEUN_H_

#include "liquidcrystal_i2c.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "encoder.h"



typedef struct  {   // Structure declaration
	uint8_t meunIndex;
	uint8_t meunLayer;
	uint8_t previousMeunIndex;
	uint8_t meunNeedUpdate; //is the meun need to update?

	uint8_t nowTemp;
	uint8_t targetTemp;
	uint8_t heatTime;

	uint8_t perheatTemp;
	uint8_t perheatTime;
	uint8_t reflowTemp;
	uint8_t reflowTime;

	char status[4];
	uint8_t isReflowProcessing;
	//for display meun state
	enum display_item{
		welcome,
		ReflowSoldering_select,
		Set_Perheat_temperature,
		Set_Perheat_time,
		Set_Reflow_temperature,
		Set_Reflow_time,

		PID_Auto_Tuning_select,
		PID_Auto_Tuning_wait,
		PID_Auto_Tuning_OK,
		PID_Auto_Tuning_fail,
		Reflow_Soliding_process
	};

	enum display_layer{
		layer_1,
		layer_2
	};
}MEUN_TypeDef;

void meunInit(MEUN_TypeDef *meun, int defaultPerheatTemp, int defaultPerheatTime,
		int defaultReflowTemp, int defaultReflowTime);
void startScreeen();
void reflowSoldering_select();
void _PID_Auto_Tuning_wait();
void _PID_Auto_Tuning_fail();
void reflow_Soldering_process(MEUN_TypeDef *meun);
void displayMeunHandler(MEUN_TypeDef *meun);
void selectMeunHandler(MEUN_TypeDef *meun);

void _Set_Perheat_temperature(MEUN_TypeDef *meun);
void _Set_Perheat_time(MEUN_TypeDef *meun);
void _Set_Reflow_temperature(MEUN_TypeDef *meun);
void _Set_Reflow_time(MEUN_TypeDef *meun);
void _updateCursorPosition(MEUN_TypeDef *meun);

void first_page();
void second_page();
void third_page();

// End the structure with a semicolon

#endif //__MEUN_H_
