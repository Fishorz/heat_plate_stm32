#ifndef __MEUN_H_
#define __MEUN_H_

#include "liquidcrystal_i2c.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "encoder.h"

enum display{
	ReflowSoldering_select,
	PID_Auto_Tuning_select,
	PID_Auto_Tuning_wait,
	PID_Auto_Tuning_OK,
	PID_Auto_Tuning_fail,
	Reflow_Soliding_process
};

struct meun {   // Structure declaration

	uint8_t nowTemp;
	uint8_t targetTemp;
	uint8_t heatTime;
	char status;
};
// End the structure with a semicolon

#endif //__MEUN_H_
