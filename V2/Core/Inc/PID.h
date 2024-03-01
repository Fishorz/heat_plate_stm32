 /*
------------------------------------------------------------------------------
~ File   : pid.h
~ Author : Majid Derhambakhsh
~ Version: V1.0.0
~ Created: 02/11/2021 03:43:00 AM
~ Brief  :
~ Support:
		   E-Mail : Majid.do16@gmail.com (subject : Embedded Library Support)

		   Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:

~ Attention  :

~ Changes    :
------------------------------------------------------------------------------
*/

#ifndef __PID_H_
#define __PID_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>
#include <string.h>
#include "stm32f1xx_hal.h"
/* ------------------------------------------------------------------ */


typedef struct {
	double setPoint;
	double error, lastError, PID_value;
	unsigned long startTime, currentTime, previousTime, elapsedTime;

//	double kP = 10, kI = 0.5, kD = 0.3;
	double kP, kI, kD;
	double pTerm, iTerm, dTerm;

	float tempRead;
} PID_TypeDef;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
double constrain( double x, double a, double b);
void setPidFactor(PID_TypeDef *pid, double _kP,double _kI,double _kD);

#endif /* __PID_H_ */
