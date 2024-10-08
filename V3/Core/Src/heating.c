#include "main.h"
#include "heating.h"

void init_pid(HEATING_TypeDef *heating){

	heating->Kp = 1;
	heating->Ki = 2;
	heating->Kd = 0;
	heating->dt = 0.01;
}

void cal_pid(HEATING_TypeDef *heating, float nowTemp, int32_t targetTemp){

	heating->error  =  (((float) targetTemp) - nowTemp) * 4096 + 0.5;

	if (heating->error < 16384 && heating->error >-16384){
		heating->integralError += (heating->Ki * heating->error+8192)>>14;
	}else{
		heating->integralError = 0;
	}

	heating->integralError = heating->integralError < -102400 ? -102400 : heating->integralError;
	heating->integralError = heating->integralError > 102400 ? 102400 : heating->integralError;

	heating->pwm_duty = ((heating->Kp * heating->error + 64)>>7) + ((heating->integralError+1024)>>11);

	heating->pwm_duty = heating->pwm_duty < 0 ? 0 : heating->pwm_duty;
	heating->pwm_duty = heating->pwm_duty > 200 ? 200 : heating->pwm_duty;


}
