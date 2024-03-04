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
	meun->meunUpdateState = 0;
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
	HD44780_PrintStr("Reflow Soldering<");
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr("PID Auto Tuning");
}

void _PID_Auto_Tuning_select() {
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Reflow Soldering");
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr("PID Auto Tuning<");
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
 *------------------
 *|Step:XX Time:XXX|
 *|N_T:XXX S_T:XXX |
 *------------------
 */
void reflow_Soliding_process(MEUN_TypeDef *meun) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("step:");
	HD44780_PrintStr(&(meun->status));
	HD44780_SetCursor(8, 0); //Time:
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
//	if (meun->meunUpdateState == 0) {
		if (1) {
		meun->meunUpdateState = 1;
		switch (meun->meunIndex) {
		case 0:
			reflowSoldering_select();
			debug_print("reflowSoldering \n\r");
			break;
		case 1:
			_PID_Auto_Tuning_select();
			debug_print("Tuning_select \n\r");
			break;
		case 2:
			_PID_Auto_Tuning_wait();
			debug_print("Tuning_wait \n\r");
			break;
		case 3:
			_PID_Auto_Tuning_OK();
			debug_print("Tuning_OK \n\r");
			break;
		case 4:
			_PID_Auto_Tuning_fail();
			debug_print("fail \n\r");
			break;
		case 5:
			reflow_Soliding_process(meun);
			debug_print("processing \n\r");
			break;
		default:
			return;
		}
	}
}

void selectMeunHandler(MEUN_TypeDef *meun) {
//	int _encoderState_ = 0;
//	_encoderState_ = encoderState();
	//change meun selection(pid or reflow)
	if (encoderState() > 0 && meun->meunIndex == 0) {
		meun->meunIndex = 1;
		debug_print("meunIndex = 1");
	}
	if (encoderState() < 0 && meun->meunIndex == 1) {
		meun->meunIndex = 0;
		debug_print("meunIndex = 0");
	}
	//which meun selected
	if (btnState() == 1 && meun->meunIndex == 0) {
		reflow_Soliding_process(meun);
	}
	if (btnState() == 1 && meun->meunIndex == 1) {
		_PID_Auto_Tuning_wait();
	}
}
