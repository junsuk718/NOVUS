#pragma once
/*
 * main_loop.h
 *
 *  Created on: Apr 17, 2021
 *      Author: mined
 */

#ifndef INC_MAIN_LOOP_H_
#define INC_MAIN_LOOP_H_

#include "Controller/controller.h"

SPT_Value setpoint_value;
float speed_command;
float moment_command;
MODE mode;

void main_loop(void);
void getSensor(void);

#endif /* INC_MAIN_LOOP_H_ */
