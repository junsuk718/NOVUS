#pragma once

/*
 *Setting & Management
 *  Controller's GAIN
 *		SPD_GAIN spd_gain - Speed Controller  (additionally I_gain)
 *		MNT_GAIN mnt_gain - Moment Controller (additionally I_gain)
 *		amp_gain - Decide the amount amplitude of sin wave multiplied according to stick command
 *	Set Point
 *		Target speed (setpoint of speed)
 *		Target roll_amplitude, pitch_amplitude (amplitude of sin wave)
 *		Target cyclic_shift (Cyclic Shift of sin wave)
*/
#ifndef __SETUP_H
#define __SETUP_H

#include "novus_math.h"

//!NOTE :: I_gain은 현재 사용하지 않음. 사용시 주석 해제. @mhlee (2021.03.30)
//#define I_CONTROLLER

/*
 *
*/
struct Speed_controller_gain{
    float P_gain;
    float D_gain;
    #ifdef I_CONTROLLER
        float I_gain;
    #endif
};

struct Moment_controller_gain{
    float P_gain;
    float D_gain;
    #ifdef I_CONTROLLER
        float I_gain;
    #endif
};

typedef struct Set_Point_Value{
    float speed;

    float pitch_amplitude;
    float roll_amplitude;

    float cyclic_shift;
}SPT_Value;

float AMP_GAIN;
struct Speed_controller_gain SPD_GAIN;
struct Moment_controller_gain MNT_GAIN;

#ifdef I_CONTROLLER
void setSpeedGain(float p, float d, float i);
void setMomentGain(float p, float d, float i);
#else
void setSpeedGain(float p, float d);
void setMomentGain(float p, float d);
#endif
void setAmplitudeGain(float gain);

struct Set_Point_Value setpoint(RC rc, MOTOR motor);

float setSpeed(uint16_t throttle);
float setAmplitude(uint16_t stick_pos, float current_speed, MOTOR motor);
float setCyclicShift(uint16_t roll_stick_pos, uint16_t pitch_stick_pos);

float stick2percent(uint16_t stick);

#endif
