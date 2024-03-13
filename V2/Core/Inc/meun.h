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

	uint16_t nowTemp;
	uint16_t targetTemp;
	uint16_t heatTime;

	uint16_t perheatTemp;
	uint32_t perheatTime;
	uint16_t reflowTemp;
	uint32_t reflowTime;

	char status[5];
	uint8_t isReflowProcessing;
	uint8_t isReflowDone;

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
		Reflow_Soliding_process,
		Reflow_Done
	};

	enum display_layer{
		layer_1,
		layer_2,
		layer_3
	};

	enum display_item meunIndex;
	enum display_layer meunLayer;

}MEUN_TypeDef;

void meunInit(MEUN_TypeDef *meun, int defaultPerheatTemp, int defaultPerheatTime,
		int defaultReflowTemp, int defaultReflowTime);

void setReflowing(MEUN_TypeDef *meun);
void cancelReflowing(MEUN_TypeDef *meun);
void updateDisplay(MEUN_TypeDef *meun);
void selectLayer(MEUN_TypeDef *meun, int _meunIndex);

void startScreeen();
void reflowSoldering_select();
void _PID_Auto_Tuning_wait();
void _PID_Auto_Tuning_fail();
void reflow_Soldering_process(MEUN_TypeDef *meun);
void reflow_done(MEUN_TypeDef *meun);
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
