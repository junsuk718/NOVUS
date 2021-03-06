#pragma once
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONTROLLER_H
#define __CONTROLLER_H

/* Includes ------------------------------------------------------------------*/
#include "Controller/setup.h"

#define PWM_MIN 1190
#define PWM_MAX 1850

typedef enum control_mode{
  CUT_OFF = 0,
  ARM,
  NON_MOMENT,
  MOMENT
}MODE;

float pre_error;
float integral_error;

float moment_pre_error;

uint16_t loop_time, start_time;

void controllerInit(TIM_HandleTypeDef* htimex);

float PD_Controller(float p, float d, float error);
float PID_Controller(float p, float i, float d, float error);

MODE getMode(RC rc);

float speedController(SPT_Value setpoint, MOTOR motor);
float momentController(SPT_Value* setpoint, MOTOR motor);

void outputMotor(float speed_command, float moment_command, MODE mode);
void PWM_Generator(float command);

#endif
