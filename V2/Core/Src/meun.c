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

enum display_item meunIndex;
enum display_layer meunLayer;
extern uint8_t counter;

void meunInit(MEUN_TypeDef *meun, int defaultPerheatTemp,
		int defaultPerheatTime, int defaultReflowTemp, int defaultReflowTime) {
	meun->meunIndex = 1;
	meun->previousMeunIndex = 0;
	meun->meunNeedUpdate = 1;
	meun->isReflowProcessing = 0;

	meun->perheatTemp = defaultPerheatTemp;
	meun->perheatTime = defaultPerheatTime;
	meun->reflowTemp = defaultReflowTemp;
	meun->reflowTime = defaultReflowTime;
	HD44780_Init(2);
}

void startScreeen() {
	HD44780_NoDisplay();
	HD44780_Cursor();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("HELLO STM32!!!");
	HD44780_PrintSpecialChar(0);
}

void first_page() {
	HD44780_SetCursor(1, 0);
//	HD44780_PrintStr("-xxxxxxxxxxxxxx<");
	HD44780_PrintStr("-DIY Heat Plate-");
	HD44780_SetCursor(1, 1);
	HD44780_PrintStr("Reflow Solder");
}

void second_page() {
	HD44780_SetCursor(1, 0);
//	HD44780_PrintStr("-xxxxxxxxxxxxxx<");
	HD44780_PrintStr("Set Pre Temp   ");
	HD44780_SetCursor(1, 1);
//	HD44780_PrintStr("-xxxxxxxxxxxxxx<");
	HD44780_PrintStr("Set Pre Time   ");
}

void third_page() {
	HD44780_SetCursor(1, 0);
//	HD44780_PrintStr("-xxxxxxxxxxxxxx<");
	HD44780_PrintStr("Set Reflow Temp");
	HD44780_SetCursor(1, 1);
	HD44780_PrintStr("Set Reflow Time");
}

void _updateCursorPosition(MEUN_TypeDef *meun) {
	//Clear display's ">" parts
	HD44780_SetCursor(0, 0); //1st line, 1st block
	HD44780_PrintStr(" "); //erase by printing a space
	HD44780_SetCursor(0, 1);
	HD44780_PrintStr(" ");

	//Place cursor to the new position
	//in the welcome page set cursor to 2nd line
	if (meun->meunIndex == 0) {
		HD44780_SetCursor(0, 1); // 2nd line, 1st block
		HD44780_PrintStr(">");
		return;
	}
	if (meun->meunIndex % 2 == 0) {
		HD44780_SetCursor(0, 0); // 1st line, 1st block
		HD44780_PrintStr(">");
	} else {
		HD44780_SetCursor(0, 1); // 2nd line, 1st block
		HD44780_PrintStr(">");
	}
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
void _Set_Perheat_temperature(MEUN_TypeDef *meun) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
//	HD44780_PrintStr("-XXXXXXXXXXXXXX-");
	HD44780_PrintStr("Perheat Temp =  ");
	itoa(meun->perheatTemp, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
}

void _Set_Perheat_time(MEUN_TypeDef *meun) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
//	HD44780_PrintStr("-XXXXXXXXXXXXXX-");
	HD44780_PrintStr("Perheat Time =  ");
	itoa(meun->perheatTime, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
}

void _Set_Reflow_temperature(MEUN_TypeDef *meun) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
//	HD44780_PrintStr("-XXXXXXXXXXXXXX-");
	HD44780_PrintStr("Reflow Temp =   ");
	itoa(meun->reflowTemp, displayTemp, 10);
	HD44780_PrintStr(displayTemp);
}

void _Set_Reflow_time(MEUN_TypeDef *meun) {
	char displayTemp[10];
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
//	HD44780_PrintStr("-XXXXXXXXXXXXXX-");
	HD44780_PrintStr("Reflow Time =   ");
	HD44780_SetCursor(0, 1);
	itoa(meun->reflowTime, displayTemp, 10);
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

//To control what should displaying
void displayMeunHandler(MEUN_TypeDef *meun) {
	//*_*hard code update state to Ldisplay something

	if (meun->meunNeedUpdate) {
		printf("Update Display \n\r");
		meun->meunNeedUpdate = 0;

		switch (meun->meunLayer) {
		case layer_1:

			switch (meun->meunIndex) {
			case ReflowSoldering_select:
				first_page();
				debug_print("in the first_page \n\r");
				break;
			case Set_Perheat_temperature:
			case Set_Perheat_time:
				second_page();
				debug_print("in the second_page \n\r");
				break;
			case Set_Reflow_temperature:
			case Set_Reflow_time:
				third_page();
				debug_print("in the third_page \n\r");
				break;
			case Reflow_Soliding_process:
				reflow_Soldering_process(meun);
				debug_print("Reflow Soldering Process \n\r");
				break;
			default:
				return;
			}
			_updateCursorPosition(meun);
			break;

		case layer_2:

			switch (meun->meunIndex) {
			case (ReflowSoldering_select):
				printf("kick in to Reflow Soldering Process \r\n");
				meun->meunIndex = Reflow_Soliding_process;
				meun->isReflowProcessing = 1;
				reflow_Soldering_process(meun);
				meun->meunNeedUpdate = 1;
				break;
			case (Set_Perheat_temperature):
				printf("kick in to Set_Perheat_temperature \r\n");
				_Set_Perheat_temperature(meun);
				break;
			case (Set_Perheat_time):
				printf("kick in to Set_Perheat_time \r\n");
				_Set_Perheat_temperature(meun);
				break;
			case (Set_Reflow_temperature):
				printf("kick in to Set_Reflow_temperature \r\n");
				_Set_Reflow_temperature(meun);
				break;
			case (Set_Reflow_time):
				printf("kick in to Set_Reflow_time \r\n");
				_Set_Reflow_time(meun);
				break;
			}
			break;
		default:
			return;
		}
	}
}

void selectOverFlow(MEUN_TypeDef *meun) {
	//The end of the slecetion is "Set_Reflow_time"
	if (meun->meunIndex > Set_Reflow_time) {
		meun->meunIndex = Set_Reflow_time;
	} else if (meun->meunIndex < 1) {
		meun->meunIndex = 1;
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
	 */

	// To hide the meun should not show by selection
	if (meun->meunLayer == layer_1) {
		if (encoderState() > 0) {
			meun->meunIndex++;
			selectOverFlow(meun);
			meun->meunNeedUpdate = 1;
			debug_print("meunIndex = 1 \r\n");
		}
		if (encoderState() < 0) {
			meun->meunIndex--;
			selectOverFlow(meun);
			meun->meunNeedUpdate = 1;
			debug_print("meunIndex = 0 \r\n");
		}
	}

	//To let value can be change by encoder such like temp or time
	if (encoderState() > 0 && meun->meunLayer == layer_2) {
		switch (meun->meunIndex) {
		case (Set_Perheat_temperature):
			printf("Set preheart temp ++ \r\n");
			meun->perheatTemp++;
			break;
		case (Set_Perheat_time):
			printf("Set preheart time ++ \r\n");
			meun->perheatTime++;
			break;
		case (Set_Reflow_temperature):
			printf("Set reflow temp ++ \r\n");
			meun->reflowTemp++;
			break;
		case (Set_Reflow_time):
			printf("Set reflow time ++ \r\n");
			meun->reflowTime++;
			break;
		default:
			return;
		}
		meun->meunNeedUpdate = 1;
	}

	if (encoderState() < 0 && meun->meunLayer == layer_2) {
		switch (meun->meunIndex) {
		case (Set_Perheat_temperature):
			printf("Set preheart temp -- \r\n");
			meun->perheatTemp--;
			break;
		case (Set_Perheat_time):
			printf("Set preheart time -- \r\n");
			meun->perheatTime--;
			break;
		case (Set_Reflow_temperature):
			printf("Set reflow temp -- \r\n");
			meun->reflowTemp--;
			break;
		case (Set_Reflow_time):
			printf("Set reflow time -- \r\n");
			meun->reflowTime--;
			break;
		}
		meun->meunNeedUpdate = 1;
	}

	//which meun selected
	if (btnState()) {
		switch (meun->meunLayer) {
		case (layer_1):
			meun->meunLayer = layer_2;
			break;
		case (layer_2):
			meun->meunLayer = layer_1;
			break;
		default:
			return;
		}
		meun->meunNeedUpdate = 1;
	}
}
