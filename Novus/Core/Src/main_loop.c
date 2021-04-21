#include "main_loop.h"

void main_loop(){
	motor.rpm = calcRPM(motor.pre_ang - motor.ang);
	setpoint_value = setpoint(rc);
	mode = getMode(rc);

	if(mode == NON_MOMENT){
#if 0
		speed_command = motor.rpm + speedController(setpoint_value, motor);
		moment_command = 0;
#else
		speed_command = map(rc.throttle, RC_MIN, RC_MAX, PWM_MIN, PWM_MAX);
#endif
	}else if(mode == MOMENT){
		moment_command = motor.rpm + momentController(setpoint_value, motor);
		speed_command = 0;
	}else{
		speed_command = 0;
		moment_command = 0;
	}

	outputMotor(speed_command, moment_command, mode);
}
