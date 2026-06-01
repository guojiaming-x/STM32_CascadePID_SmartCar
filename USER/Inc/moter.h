#ifndef __MOTER_H
#define __MOTER_H
#include "stdint.h"
typedef enum{
   LEFT=0,
   RIGHT=1

}Motor;
float limitOutput(float output,const float MAX_OUTPUT_ABS);
float limit(float output,const float MAX_OUTPUT_ABS);
float myabs(float input);
void runMotorPWMA(Motor l_or_r, int16_t pwm_val);
#endif
