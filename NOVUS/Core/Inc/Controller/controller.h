#pragma once
/**
  ******************************************************************************
  * @file           : controller.h
  * @brief          : Header for controller.c file.
  *                   This file contains the common defines of the application.
  * @author NOVUS Graduation Project Team
  ******************************************************************************
  * @details
  *
  * Setting & Management
  * 
  * as5147 SETTING
  *     as5147_Init - as5147 initialize
  *		as5147_setZeroPosition - set angle to zeroposition
  *		as5147_readPosition - read angle from as5147
  *
  * as5147 R/W
  * 	registerRead - read register value
  * 	registerWrite - write register value
  * 	packCommandFrame - 
  * 	calcParity
  * 
  * angle caculator
  * 	calcRPM - calculate RPM
  *
  ******************************************************************************
  */

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONTROLLER_H
#define __CONTROLLER_H

/* Includes ------------------------------------------------------------------*/
#include "Controller/setup.h"

#define PWM_MIN 1190
#define PWM_MAX 1850

/**
 * @brief RC 비행 모드에 사용될 모드 종류들
 * 
 */
typedef enum control_mode{
  CUT_OFF = 0,  /*!< all process stop */
  ARM,          /*!< arming motor(set motor to MIN speed )*/
  NON_MOMENT,   /*!< there is no moment control in this mode*/
  MOMENT        /*!< there is*/
}MODE;

float pre_error;
float integral_error;
uint16_t loop_time, start_time;

void controllerInit(TIM_HandleTypeDef* htimex);

float PD_Controller(float p, float d, float error);
float PID_Controller(float p, float i, float d, float error);

MODE getMode(RC rc);

float speedController(SPT_Value setpoint, MOTOR motor);
float momentController(SPT_Value setpoint, MOTOR motor);

void outputMotor(float speed_command, float moment_command, MODE mode);
void PWM_Generator(float command);

#endif
