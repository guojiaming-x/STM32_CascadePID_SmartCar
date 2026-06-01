#include "tim.h"
#include "usart.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"

Encoder ecd;
PID vec_left;
PID pos_left;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3){
		updateEncoderLoopOverflowVersion(&ecd, 10);
		updatePID(&pos_left, ecd.position.angle);
		setPIDTarget(&vec_left, pos_left.output);
		updatePID(&vec_left, ecd.velocity.angular);
		runMotorPWMValFB(LEFT, vec_left.output);
		//printf("%.2f,%.2f,%.2f,%.2f,%.2f\n",pos_left.target, pos_left.input, pos_left.output,vec_left.input,vec_left.output);
		//printf("%.2f,%.2f,%.2f\n",vec_left.target, vec_left.input, vec_left.output);
	}
}

void myCarControlCodeInit(){
	Parameter left_param = {4,30,500,0.065,&htim2};
	initEncoder(&ecd,left_param);
	//vec pid init
	initPID(&vec_left, 2100, 5000);
	setPIDParam(&vec_left, 10, 0.5,0.0);
	
	//pos pid init
	initPID(&pos_left, 300, 5000);// 300 -> rpm
	setPIDParam(&pos_left, 0.9, 0.0,0.0);
	setPIDTarget(&pos_left, 720);
	//runMotorPWMValFB(LEFT,+1000);
}



