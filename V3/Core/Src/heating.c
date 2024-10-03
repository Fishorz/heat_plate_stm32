#include "main.h"
#include "heating.h"

void init_pid(HEATING_TypeDef *heating){

	heating->Kp = 0.1;
	heating->Ki = 0;
	heating->Kd = 0;
	heating->dt = 0.1f;
}

void cal_pid(HEATING_TypeDef *heating, int32_t nowTemp, int32_t targetTemp){

	heating->error  =  targetTemp - nowTemp;
	heating->integralError += heating->error + heating->previousError;
	heating->derivative = (heating->error - heating->previousError)/heating->dt;

	heating->P = heating->Kp * heating->error;
	heating->I = heating->Ki * heating->integralError * (heating->dt/2.0);
	heating->D = heating->Kd * heating->derivative;

	heating->uPid = heating->P + heating->I + heating->D;

	if(heating->uPid > 1)
		{
		heating->uPid = 1;
		}
		if(heating->uPid < 0.0)
		{
			heating->uPid = 0.0;
		}
		float duty = heating->uPid * 200.0;
		heating->pwm_duty = (int) duty;
		heating->previousError = heating->error;
}
