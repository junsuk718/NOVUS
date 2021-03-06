#include "Controller/controller.h"

TIM_HandleTypeDef* time_handler;

void controllerInit(TIM_HandleTypeDef* htimex){
	time_handler = htimex;
	time_handler->Instance->CCR1 = 1000;
#ifdef I_CONTROLLER
	integral_error = 0;
	setSpeedGain(0.132, 0.01147, 0.00015);
#else
	//setSpeedGain(0.11, 0.0063);
	//setMomentGain(0.11, 0.0063);
	setSpeedGain(0.025, 0.0008);
	setMomentGain(0.03, 0);
#endif
	setAmplitudeGain(70);

	HAL_TIM_PWM_Start(time_handler, TIM_CHANNEL_1);
}

float PD_Controller(float p, float d, float error){
    float control_value = 0;

    float proportion_controll_value = error * p;

    float differential_controll_value = ((error - pre_error) / (loop_time/100000.)) * d;

    control_value = proportion_controll_value + differential_controll_value;

    return control_value;
}

float PID_Controller(float p, float d, float i, float error){
    float control_value = 0;

    float proportion_controll_value = error * p;

    integral_error += error;
    float integral_controll_value = integral_error * i;

    float differential_controll_value = ((error - pre_error) / (loop_time/100000.)) * d;

    control_value = proportion_controll_value + differential_controll_value + integral_controll_value;

    return control_value;
}

MODE getMode(RC rc){
	if(rc.aux3 > 1300){
		if(rc.aux1 < 500){
			return ARM;
		}else if(rc.aux1 > 500 && rc.aux1 < 1400){
			return NON_MOMENT;
		}else{
			return MOMENT;
		}
	}else{
		return CUT_OFF;
	}
}

float speedController(SPT_Value setpoint, MOTOR motor){
    float error = setpoint.speed - motor.rpm;

#ifdef I_CONTROLLER
    float control_value = PID_Controller(speed_gain.P_gain, speed_gain.D_gain, speed_gain.I_gain, error);
#else
    float control_value = PD_Controller(speed_gain.P_gain, speed_gain.D_gain, error);
#endif

    pre_error = error;

    return control_value;
}

float momentController(SPT_Value* setpoint, MOTOR motor){
	setpoint->moment_speed = setpoint->speed + (sin((motor.ang*(2*PI/360.)) + setpoint->cyclic_shift) * setpoint->amplitude);

    float error = setpoint->moment_speed - motor.rpm;

    if(setpoint->moment_speed <= setpoint->speed + 1 && setpoint->moment_speed >= setpoint->speed - 1 ){
		error = 0;
	}

    float control_value = PD_Controller(moment_gain.P_gain, moment_gain.D_gain, error);

    moment_pre_error = error;

	return control_value;
}

volatile float command = 0;

void outputMotor(float speed_command, float moment_command, MODE mode){

    //! NOTE :: rpm command to throttle percent scalar
    switch(mode){
        case CUT_OFF:
#ifdef I_CONTROLLER
        	integral_error = 0;
#endif
        	pre_error = 0;
            command = 1000;
            break;
        case ARM:
#ifdef I_CONTROLLER
        	integral_error = 0;
#endif
        	pre_error = 0;
            command = 1200;
            break;
        case NON_MOMENT:
            command = motor.pwm + (speed_command / 50.);
            if(command < PWM_MIN) command = PWM_MIN;
            else if(command > PWM_MAX) command = PWM_MAX;
            break;
        case MOMENT:
            //command = motor.pwm + (speed_command / 10) + (moment_command / 10);
        	command = motor.pwm + (moment_command / 50.);
            if(command < PWM_MIN) command = PWM_MIN;
            else if(command > PWM_MAX) command = PWM_MAX;
            break;
    }

    PWM_Generator(command);
}

void PWM_Generator(float command){
    motor.pwm = command;
    time_handler->Instance->CCR1 = command;
}
