#include "Controller/novus_math.h"

float map(float target, int from_min, int from_max, int to_min, int to_max){
    float mult = (float)(to_max - to_min) / (float)(from_max - from_min);
    target = target - from_min;
    return to_min + (target * mult);
}

float getLPF_RPM(float raw_rpm, float pre_rpm, float loop_time){

	float lpf_rpm = ((LPF_GAIN * pre_rpm) + (loop_time * raw_rpm)) / (LPF_GAIN + loop_time);

	return lpf_rpm;
}
