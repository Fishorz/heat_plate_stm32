 /*
------------------------------------------------------------------------------
~ File   : pid.c
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

#include "pid.h"
extern uint32_t pid_counter;
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

double constrain( double x, double a, double b){
    if(x < a) {
        return a;
    }else if(b < x) {
        return b;
    }
    else{
    	return x;
    }
}

/* ~~~~~~~~~~~~~~~~~ Initialize ~~~~~~~~~~~~~~~~ */

void setPidFactor(PID_TypeDef *factor, double _kP,double _kI,double _kD){
	factor->kP = _kP;
	factor->kI = _kI;
	factor->kD = _kD;
}

/* ~~~~~~~~~~~~~~~~~ Calculate Function ~~~~~~~~~~~~~~~~ */
double PIDcalculate(PID_TypeDef *pid, double ambTemp, double currentTemp){
	//for test setpoint
	pid->setPoint = ambTemp;
	pid->tempRead =currentTemp;
	pid->error = pid->setPoint - pid->tempRead;
    // Proportional
	pid->pTerm = pid->error;
	// Integral
	    if (pid->error > -3 && pid->error < 3)
	    	pid->iTerm += pid->error;
	    // Anti-wind-up
	    pid->iTerm = constrain(pid->iTerm, 0, 100);
	    // Derivative
	    pid->dTerm = (pid->error - pid->lastError) / pid_counter * 0.001; //ms
	    // Calculate PID
	    pid->PID_value = pid->kP * pid->pTerm + pid->kI * pid->iTerm + pid->kD * pid->dTerm;
	    // Deadband
//	    PID_value = constrain(PID_value, 0, 255);
	    pid->lastError = pid->error;
//	    printf("pid_counter = %lu\r\n", pid_counter);
	    pid_counter = 0;
	    return pid->PID_value;
}
