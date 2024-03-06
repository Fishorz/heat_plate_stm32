/*
 * meun.c
 *
 *  Created on: Jan 19, 2024
 *      Author: sky.chu
 */

/*
 Meun preview
 Start Page->

 ""main""
 ------------------
 |ReflowSoldering<|
 |PID Auto Tuning |
 ------------------

 ------------------
 |ReflowSoldering |
 |PID Auto Tune  <|
 ------------------

 ""In pid Auto tuning""
 ------------------
 |PID Auto Tuning |
 |please wait.	 |
 ------------------
 ------------------
 |PID Auto Tuning |
 |please wait..	 |
 ------------------
 ------------------
 |PID Auto Tuning |
 |please wait...	 |
 ------------------
 ------------------
 |PID Auto Tuning |
 |PID Tuning OK   |
 ------------------
 ------------------
 |PID Auto Tuning |
 |PID Tuning Fail |
 ------------------

 In reflow soliding

 ------------------
 |Step:XX Time:XXX|
 |N_T:XXX S_T:XXX |
 ------------------


 */
#include <meun.h>
#include "encoder.h"
#include "debug_print.h"

//uint8_t meunIndex = 1;
//uint8_t previousMeunIndex = 0;
//uint8_t meunUpdateState;

enum display meunIndex;
extern uint8_t counter;



void meunInit(MEUN_TypeDef *meun){
	meun->meunIndex = 0;
	meun->previousMeunIndex = 0;
	meun->meunNeedUpdate = 1;

	meun->isReflowProcessing = 0;
	HD44780_Init(2);
}

void startScreeen() {
	HD44780_Clear();
	HD44780_NoDisplay();
	HD44780_Cursor();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("HELLO STM32!!!");
	HD44780_PrintSpecialChar(0);
}

void reflowSoldering_select() {
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Reflow Solder<");
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr("PID Auto Tune");
}

void _PID_Auto_Tuning_select() {
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Reflow Solder");
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr("PID Auto Tune<");
}

void _PID_Auto_Tuning_wait() {
	uint8_t _waitState = counter % 100;
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("PID Auto Tuning");
	HD44780_SetCursor(0, 1);
	switch (_waitState) {
	case (1):
		HD44780_PrintStr("waiting");
		break;
	case (2):
		HD44780_PrintStr("waiting.");
		break;
	case (3):
		HD44780_PrintStr("waiting..");
		break;
	case (4):
		HD44780_PrintStr("waiting...");
		break;
	default:
		return;
	}
}

void _PID_Auto_Tuning_OK() {
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("PID Auto Tuning");
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr("PID Tuning OK");
}

void _PID_Auto_Tuning_fail() {
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("PID Auto Tuning");
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr("PID Tuning Fail");
}
/*
 		Set_Perheat_temperature,
		Set_Perheat_time,
		Set_Reflow_temperature,
		Set_Reflow_time,
 */
void _Set_Perheat_temperature(int perheatTemperature) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Perheat Temperature =");
	itoa(perheatTemperature, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
}

void _Set_Perheat_time(int perheatTime) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Perheat Time = ");
	itoa(perheatTime, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
}

void _Set_Reflow_temperature(int reflowTemperature) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Reflow Temperature = ");
	itoa(reflowTemperature, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
}

void _Set_Reflow_time(int reflowTime) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Reflow Time =");
	HD44780_SetCursor(0, 1);
	itoa(reflowTime, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
}
/*
 *------------------
 *|Step:XX Time:XXX|
 *|N_T:XXX S_T:XXX |
 *------------------
 */
void reflow_Soldering_process(MEUN_TypeDef *meun) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("step:");
	HD44780_PrintStr(&(meun->status));
	HD44780_SetCursor(8, 0); //Time from start soldering
	HD44780_PrintStr("Time:");
	itoa(meun->heatTime, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr("N_T:");
	itoa(meun->nowTemp, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
	HD44780_SetCursor(8, 0);
	itoa(meun->targetTemp, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
}

void displayMeunHandler(MEUN_TypeDef *meun) {
	//*_*hard code update state to Ldisplay something
	if (meun->meunNeedUpdate) {
		printf("Update Display \n\r");
		meun->meunNeedUpdate = 0;
		switch (meun->meunIndex) {
		case ReflowSoldering_select:
			reflowSoldering_select();
			debug_print("Reflow Soldering select \n\r");
			break;
		case PID_Auto_Tuning_select:
			_PID_Auto_Tuning_select();
			debug_print("PID_Auto Tuning select \n\r");
			break;
		case PID_Auto_Tuning_wait:
			_PID_Auto_Tuning_wait();
			debug_print("Tuning_wait \n\r");
			break;
		case PID_Auto_Tuning_OK:
			_PID_Auto_Tuning_OK();
			debug_print("Tuning_OK \n\r");
			break;
		case PID_Auto_Tuning_fail:
			_PID_Auto_Tuning_fail();
			debug_print("fail \n\r");
			break;
		case Reflow_Soliding_process:
			reflow_Soldering_process(meun);
			debug_print("Reflow Soldering Process \n\r");
			break;
		case Set_Perheat_temperature:
//			reflow_Soldering_process(meun);
//			debug_print("Reflow Soldering Process \n\r");
			break;
		case Set_Perheat_time:
//			reflow_Soldering_process(meun);
//			debug_print("Reflow Soldering Process \n\r");
			break;
		case Set_Reflow_temperature:
//			reflow_Soldering_process(meun);
//			debug_print("Reflow Soldering Process \n\r");
			break;
		case Set_Reflow_time:
//			reflow_Soldering_process(meun);
//			debug_print("Reflow Soldering Process \n\r");
			break;
		default:
			return;
		}
	}
}

void selectMeunHandler(MEUN_TypeDef *meun) {
	/*
	 * change meun selection
	 * Start Reflow
	 * Edit Perheat_temperature
	 * Edit Perheat_time
	 * Edit Reflow_temperature
	 * Edit Reflow_time
	 * */

	if (encoderState() > 0 && meun->meunIndex == ReflowSoldering_select) {
		meun->meunIndex = PID_Auto_Tuning_select;
		meun->meunNeedUpdate = 1;
		debug_print("meunIndex = 1 \r\n");
	}
	if (encoderState() < 0 && meun->meunIndex == PID_Auto_Tuning_select) {
		meun->meunIndex = ReflowSoldering_select;
		meun->meunNeedUpdate = 1;
		debug_print("meunIndex = 0 \r\n");
	}

	//which meun selected
	//From Meun Reflow Soliding select to Reflow Soliding process
	if (btnState() == 1 && meun->meunIndex == ReflowSoldering_select) {
		printf("kick in to Reflow Soldering Process \r\n");
		meun->meunIndex = Reflow_Soliding_process;
		meun->isReflowProcessing = 1;
		reflow_Soldering_process(meun);
		meun->meunNeedUpdate = 1;
	}
	// From PID Auto Tuning select to PID Auto Tuning
	if (btnState() == 1 && meun->meunIndex == PID_Auto_Tuning_select) {
		printf("kick in to Running Auto Tune PID \r\n");
		meun->meunIndex = PID_Auto_Tuning_wait;
		meun->meunNeedUpdate = 1;
	}
	// From Reflow Soliding process to Meun and selecting Reflow Soldering
	if (btnState() == 1 && meun->meunIndex == Reflow_Soliding_process) {
		printf("return to Meun \r\n");
		meun->isReflowProcessing = 0;
		meun->meunIndex = ReflowSoldering_select;
		meun->meunNeedUpdate = 1;
	}
}
