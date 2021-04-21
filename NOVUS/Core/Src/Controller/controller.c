#include "Controller/controller.h"

TIM_HandleTypeDef* time_handler;

void controllerInit(TIM_HandleTypeDef* htimex){
	time_handler = htimex;
	time_handler->Instance->CCR3 = 1000;
#ifdef I_CONTROLLER
	setSpeedGain(7, 4.5, 0);
#else
	setSpeedGain(1, 1.5);
#endif
	setAmplitudeGain(1);

	HAL_TIM_PWM_Start(time_handler, TIM_CHANNEL_3);
}

float PD_Controller(float p, float d, float error){
    float control_value = 0;

    float proportion_controll_value = error * p;
#if 0
    float differential_controll_value = ((pre_error - error) / loop_time) * d;
#else
    float differential_controll_value = (pre_error - error) * d;
#endif

    control_value = proportion_controll_value + differential_controll_value;

    return control_value;
}

float PID_Controller(float p, float d, float i, float error){
    float control_value = 0;

    float proportion_controll_value = error * p;
    integral_error += error;
    float integral_controll_value = integral_error * i;
#if 0
    float differential_controll_value = ((pre_error - error) / loop_time) * d;
#else
    float differential_controll_value = (pre_error - error) * d;
#endif

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

float momentController(SPT_Value setpoint, MOTOR motor){
	return 0;
}

void outputMotor(float speed_command, float moment_command, MODE mode){
    float command;

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
            command = map(speed_command, 0, 59000, 1190, 2000);
            break;
        case MOMENT:
            command = map(moment_command, 0, 59000, 1190, 2000);
            break;
    }

    PWM_Generator(command);
}

void PWM_Generator(float command){
    motor.pwm = command;
    time_handler->Instance->CCR3 = command;
}
