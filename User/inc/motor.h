#ifndef __MOTOR_H
#define __MOTOR_H

//下面一会删除
#include "stdint.h"
//上面一会删除

typedef enum {
	LEFT = 0,
	RIGHT=1
}Motor;


void runMotorPWMValFB(Motor l_or_r, int16_t pwm_val);

#endif /* __MOTOR_H */

