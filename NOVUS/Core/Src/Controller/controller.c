#include "header.h"

float PD_Controller(float p, float d, float error){
    float control_value = 0;

    float proportion_controll_value = error * p;
    float differential_controll_value = ((pre_error - error) / loop_time) * d;

    control_value = proportion_controll_value + differential_controll_value;

    return control_value;
}

float PID_Controller(float p, float i, float d, float error){
    float control_value = 0;

    float proportion_controll_value = error * p;
    integral_error += error;
    float integral_controll_value = integral_error * i;
    float differential_controll_value = ((pre_error - error) / loop_time) * d;

    control_value = proportion_controll_value + differential_controll_value + integral_controll_value;

    return control_value;
}

float SpeedController(SPT_Value setpoint, MOTOR motor){
    float error = motor.rpm - setpoint.speed;

#ifdef I_CONTROLLER
    float control_value = PID_Controller(SPD_GAIN.P_gain, SPD_GAIN.I_gain, SPD_GAIN.I_gain, error);
#else
    float control_value = PD_Controller(speed_gain.P_gain, speed_gain.D_gain, error);
#endif

    return control_value;
}

void outputMotor(float speed_command, float moment_command, MODE mode){
    float command;

    //! NOTE :: rpm command to throttle percent scalar
    switch(mode){
        case CUT_OFF:
            command = 0;
            break;
        case ARM:
            command = 20;
            break;
        case NON_MOMENT:
            command = map(speed_command, 500, 5900, 0, 100);
            break;
        case MOMENT:
            command = map(moment_command, 500, 5900, 0, 100);
            break;
    }

    PWM_Generator(command);
}

void PWM_Generator(float command){
    uint32_t pwm_command = scalarToPwm(command);
    htim1.Instance->CCR1 = pwm_command;
}

//! TODO:: PWM period(duty) setting in MX setup
uint32_t scalarToPwm(float command){
#if 1
    return (uint32_t)map(command, 0, 100, RC_MIN, RC_MAX);
#else
    return (uint32_t)map(command, 0, 100, 0, PWM_PERIOD);
#endif
}