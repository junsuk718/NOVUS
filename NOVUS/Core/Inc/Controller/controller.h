 #pragma once
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONTROLLER_H
#define __CONTROLLER_H

/* Includes ------------------------------------------------------------------*/
#include "header.h"

typedef enum control_mode{
  CUT_OFF = 0,
  ARM,
  NON_MOMENT,
  MOMENT
}MODE;

float pre_error = 0;
float integral_error = 0;

float PD_Controller(float p, float d, float error);
float PID_Controller(float p, float i, float d, float error);

float SpeedController(SPT_Value setpoint, MOTOR motor);
float MomentController(SPT_Value setpoint, MOTOR motor);

void outputMotor(float speed_command, float moment_command, MODE mode);
void PWM_Generator(float command);

#endif