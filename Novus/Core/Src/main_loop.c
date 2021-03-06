#include "main_loop.h"

void main_loop(void){
	setpoint_value = setpoint(rc);
	mode = getMode(rc);

	if(mode == NON_MOMENT){
		speed_command = speedController(setpoint_value, motor);
	}else if(mode == MOMENT){
		speed_command = speedController(setpoint_value, motor);
		moment_command = momentController(&setpoint_value, motor);
	}else{
		speed_command = 0;
		moment_command = 0;
	}

	outputMotor(speed_command, moment_command, mode);
}

void getSensor(void){
	motor.pre_ang = motor.ang;
	sens_time = HAL_GetTick() - sens_start;
	motor.ang = map(as5147_readPosition(), 180, 360, 0, 360);
	sens_start = HAL_GetTick();

	motor.pre_rpm = motor.rpm;
	motor.rpm = calcRPM(motor.pre_ang - motor.ang, sens_time/100000.);
	motor.rpm = getLPF_RPM(motor.rpm, motor.pre_rpm, sens_time/100000.);
}
