#include "main_loop.h"

void main_loop(){
	setpoint_value = setpoint(rc);
	mode = getMode(rc);

	if(mode == NON_MOMENT){
		speed_command = motor.rpm + speedController(setpoint_value, motor);
		moment_command = 0;
	}else if(mode == MOMENT){
		moment_command = motor.rpm + momentController(setpoint_value, motor);
		speed_command = 0;
	}else{
		speed_command = 0;
		moment_command = 0;
	}

	outputMotor(speed_command, moment_command, mode);
}
