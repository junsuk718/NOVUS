#include "Controller/novus_math.h"

float map(float target, int from_min, int from_max, int to_min, int to_max){
    float mult = (float)(to_max - to_min) / (float)(from_max - from_min);
    target = target - from_min;
    return to_min + (target * mult);
}