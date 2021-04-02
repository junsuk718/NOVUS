#include "setup.h"

#ifdef I_CONTROLLER
void setSpeedGain(float p, float d, float i){
    SPD_GAIN.P_gain = p;
    SPD_GAIN.D_gain = d;
    SPD_GAIN.P_gain = i;
}

void setMomentGain(float p, float d, float i){
    MNT_GAIN.P_gain = p;
    MNT_GAIN.D_gain = d;
    MNT_GAIN.P_gain = i;
}
#else
void setSpeedGain(float p, float d){
    SPD_GAIN.P_gain = p;
    SPD_GAIN.D_gain = d;
}

void setMomentGain(float p, float d){
    MNT_GAIN.P_gain = p;
    MNT_GAIN.D_gain = d;
}
#endif

void setAmplitudeGain(float gain){
    AMP_GAIN = gain;
}

struct Set_Point_Value setpoint(RC rc, MOTOR motor){
    SPT_VALUE.speed = setSpeed(rc.throttle);
    SPT_VALUE.roll_amplitude = setAmplitude(rc.roll, SPT_VALUE.speed, motor);
    SPT_VALUE.pitch_amplitude = setAmplitude(rc.pitch, SPT_VALUE.speed, motor);
    SPT_VALUE.cyclic_shift = setCyclicShift(rc.roll, rc.pitch);
}

float setSpeed(uint16_t throttle){
    float throttle_percent = stick2percent(throttle);
    
    return map_float(throttle_percent, 0, 100, 500, 5900);
}

float setAmplitude(uint16_t stick_pos, float setpoint_speed, MOTOR motor){
    float stick_cmd = stick2percent(stick_pos);

    return setpoint_speed + ((stick_cmd * AMP_GAIN) * sin(motor.angle));
}

float setCyclicShift(uint16_t roll_stick_pos, uint16_t pitch_stick_pos){
    
}

float stick2percent(uint16_t stick){
    float val = map(stick, RC_MIN, RC_MAX, 0, 10000);
    return val/100.0;
}
