/*
 * meun.c
 *
 *  Created on: Sep 09, 2024
 *      Author: sky.chu
 */

/*
 preview
 Start Page->
 In standby
 ------------------
 |Standby  		  |
 |N_T:XXX  S_T:XXX|
 ------------------

 In Heating
 ------------------
 |Heating  		  |
 |N_T:XXX  S_T:XXX|
 ------------------

In Error Display
 ------------------
 |Error  		  |
 |XXXXX     N_T:  |
 ------------------
 */
#include <meun.h>
#include "encoder.h"
#include "main.h"
#include "config.h"

//extern uint16_t counter;

void meunInit(MEUN_TypeDef *meun, int defaultTemp) {
	meun->meunNeedUpdate = 1;
	meun->meunIndex = Standby;
	meun->nowTemp = 0;
	meun->errorOccur = 0;
	meun->targetTemp = defaultTemp;
	HD44780_Init(2);
}

/*-------------------------public function------------------------------------*/

/*-------------------------pv function----------------------------------------*/
void startScreeen(MEUN_TypeDef *meun) {
	HD44780_NoDisplay();
	HD44780_Cursor();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("HELLO STM32!!!");
	HD44780_PrintSpecialChar(0);
}

void standby_page(MEUN_TypeDef *meun) {
	if (meun->lastIndex != Standby){
		HD44780_Clear();
		HD44780_SetCursor(1, 0);
	//	HD44780_PrintStr("-xxxxxxxxxxxxxx<");
		HD44780_PrintStr("Standby        ");
		HD44780_SetCursor(0, 1);
		HD44780_PrintStr("N_T:");
		HD44780_SetCursor(9, 1);
		HD44780_PrintStr("S_T:");
	}

	char displayNowTemp[15];
	char displayTargetTemp[15];
	itoa(meun->nowTemp, displayNowTemp, 10);
	itoa(meun->targetTemp, displayTargetTemp, 10);
	HD44780_SetCursor(4, 1);
	HD44780_PrintStr(displayNowTemp);
	HD44780_SetCursor(13, 1);
	HD44780_PrintStr(displayTargetTemp);
}

void heating_page(MEUN_TypeDef *meun) {
	if (meun->lastIndex != Heating){
		HD44780_Clear();
		HD44780_SetCursor(0, 0);
	//	HD44780_PrintStr("-xxxxxxxxxxxxxx<");
		HD44780_PrintStr("Heating        ");
		HD44780_SetCursor(0, 1);
		HD44780_PrintStr("N_T:");
		HD44780_SetCursor(9, 1);
		HD44780_PrintStr("S_T:");
	}


	char displayNowTemp[15];
	char displayTargetTemp[15];
	itoa(meun->nowTemp, displayNowTemp, 10);
	itoa(meun->targetTemp, displayTargetTemp, 10);
	HD44780_SetCursor(4, 1);
	HD44780_PrintStr(displayNowTemp);
	HD44780_SetCursor(13, 1);
	HD44780_PrintStr(displayTargetTemp);
}

void error_page(MEUN_TypeDef *meun, ERROR_TypeDef *_error){
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Error");
	HD44780_SetCursor(0, 1);

}
//To control what should displaying
void displayMeunHandler(MEUN_TypeDef *meun, ERROR_TypeDef *_error) {
	//*_*hard code update state to Ldisplay something
	if (meun->meunNeedUpdate) {
		meun->meunNeedUpdate = 0;

		if(meun->targetTemp < 100){
			HD44780_SetCursor(15, 1);
			HD44780_PrintStr(" ");
		}

		if(meun->nowTemp < 100){
			HD44780_SetCursor(6, 1);
			HD44780_PrintStr(" ");
		}

		switch (meun->meunIndex) {
//		case welcome:
//			startScreeen(meun);
//			break;
		case Standby:
			standby_page(meun);
			meun->lastIndex = Standby;
			break;
		case Heating:
			heating_page(meun);
			meun->lastIndex = Heating;
			break;
		case Error_State:
			error_page(meun, _error);
			meun->lastIndex = Error_State;
			break;
		default:
			return;
		}
	}
}

void selectMeunHandler(MEUN_TypeDef *meun, ENCODER_TypeDef *encoder) {
	/*
	 * Standby
	 * Start Heating
	 */
	//which meun selected
	int temp_ = encoderState(encoder) ;
	if(temp_ != 0){
		if (temp_ == 1) {
			meun->targetTemp++;
			meun->meunNeedUpdate = 1;
		} else if (temp_ == -1) {
			meun->targetTemp--;
			meun->meunNeedUpdate = 1;
		}
	}

	if (meun->targetTemp > MAX_TEMP) {
		meun->targetTemp = MAX_TEMP;
	} else if (meun->targetTemp < MIN_TEMP) {
		meun->targetTemp = MIN_TEMP;
	}

	if (btnState(encoder)) {
		switch (meun->meunIndex) {
		case (Standby):
			meun->meunIndex = Heating;
			meun->meunNeedUpdate = 1;
			break;
		case (Heating):
			meun->meunIndex = Standby;
			meun->meunNeedUpdate = 1;
			break;
		default:
			break;
		}
	}
}

