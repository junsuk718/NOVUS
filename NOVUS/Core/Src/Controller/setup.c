#include "Controller/setup.h"

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

float getStickPercent(uint16_t stick_pos){
    float percent = map(stick_pos, RC_MIN, RC_MAX, 0, 10000) / 100.0;

    return percent
}

/*
 * '+'Vector = UP/RIGHT
 * '-'Vector = DOWN/LEFT
*/
float getStickVector(uint16_t stick_pos){
    float vector = map(stick_pos, RC_MIN, RC_MAX, -10000, 10000) / 100.0;

    return vector;
}

float getStickScalar(float stick_vector){
    float stick_scalar = 0;

    if(stick_vector < 0){
        stick_scalar = stick_vector * (-1);
    }else{
        stick_scalar = stick_vector;
    }

    return stick_scalar;
}

float checkMargin(float stick_vector){
    if(stick_vector > MARGIN_RANGE*(-1) && stick_vector < MARGIN_RANGE){
        stick_vector = 0;
    }
    return stick_vector;
}

SPT_Value setpoint(SPT_Value setpoint, RC rc, MOTOR motor){
    setpoint.speed = setSpeed(rc.throttle);
    setpoint.amplitude = setAmplitude(rc, SPT_VALUE.speed, motor);
    setpoint.cyclic_shift = setCyclicShift(rc.roll, rc.pitch);

    return setpoint;
}

float setSpeed(uint16_t throttle){
    float throttle_percent = getStickPercent(throttle);

    //!NOTE :: Percent to RPM @mhlee
    float speed = map(throttle_percent, 0, 100, 500, 5900);
    
    return speed;
}

float setAmplitude(RC rc, float setpoint_speed, MOTOR motor){
    float roll_scalar = getStickScalar(getStickVector(rc.roll));
    float pitch_scalar = getStickScalar(getStickVector(rc.pitch));

    float cmd_scalar = (roll_scalar * 0.5) + (pitch_scalar * 0.5);

    float amplitude = (cmd_scalar * AMP_GAIN);

    return amplitude;
}

float setCyclicShift(uint16_t roll_stick_pos, uint16_t pitch_stick_pos){
    float roll_vector = getStickVector(roll_stick_pos);
    float pitch_vector = getStickVector(pitch_stick_pos);

    roll_vector = checkMargin(roll_vector);
    pitch_vector = checkMargin(pitch_vector);

    float shift = 0;

    if(roll_vector == 0 && pitch_vector == 0){
        shift = 0;
    }else if(roll_vector == 0 && pitch_vector != 0){
        if(roll_vector < 0){
            shift = PI;
        }else{
            shift = 0;
        }
    }else if(roll_vector != 0 && pitch_vector == 0){
        if(pitch_vector < 0){
            shift = (3 * PI) / 2.0;
        }else{
            shift = PI / 2.0;
        }
    }else{
        float shift_ratio = (PI/2) * (pitch_vector / (roll_vector+pitch_vector));

        if(pitch_vector < 0){
            if(roll_vector < 0){
                shift = PI + shift_ratio
            }else{
                shift = (-1) * shift_ratio;
            }
        }else{
            if(roll_vector < 0){
                shift = PI - shift_ratio;
            }else{
                shift = shift_ratio;
            }
        }
    }

    return shift;
}