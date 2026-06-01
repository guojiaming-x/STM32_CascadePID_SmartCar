#ifndef __SERVOR_H
#define __SERVOR_H
#include "main.h"


uint32_t AngleTurn(float angle); //PWM 转角度


uint32_t AngleToPulse(int32_t angle_int); // 整数乘除，避免浮点运算，角度控制

void servo_get(float X,float Y);



                                                




#endif
