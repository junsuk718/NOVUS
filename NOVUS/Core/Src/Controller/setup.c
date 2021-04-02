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

SPT_Value setpoint(SPT_Value setpoint, RC rc, MOTOR motor){
    setpoint.speed = setSpeed(rc.throttle);
    setpoint.roll_amplitude = setAmplitude(rc.roll, SPT_VALUE.speed, motor);
    setpoint.pitch_amplitude = setAmplitude(rc.pitch, SPT_VALUE.speed, motor);
    setpoint.cyclic_shift = setCyclicShift(rc.roll, rc.pitch);

    return setpoint;
}

float setSpeed(uint16_t throttle){
    float throttle_percent = stick2percent(throttle);
    
    throttle_percent = throttle_percent * 100.0;
    
    return (map(throttle_percent, 0, 10000, 5000, 59000) / 10.0);
}

float setAmplitude(uint16_t stick_pos, float setpoint_speed, MOTOR motor){
    float stick_cmd = stick2percent(stick_pos) * 100;
    float stick_vector = map(stick_cmd, 0, 10000, -10000, 10000) / 100.0;
    if(stick_vector < 0){
        float stick_scalar = stick_vector * (-1);
    }else{
        float stick_scalar = stick_vector;
    }
    return (stick_scalar * AMP_GAIN);
}

float setCyclicShift(uint16_t roll_stick_pos, uint16_t pitch_stick_pos){
    float roll_cmd = stick2percent(stick_pos);
    float pitch_cmd = stick2percent(stick_pos);
    //!TODO :: 스틱간 비율에 따른 Shift 결정
}

//!NOTE :: 다른 기능으로 전환 가능성 다분.
float stick2percent(uint16_t stick){
    float val = map(stick, RC_MIN, RC_MAX, 0, 10000);

    return val/100.0;
}