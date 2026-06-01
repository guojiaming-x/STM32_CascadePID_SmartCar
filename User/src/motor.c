#include "motor.h"
#include "main.h"
#include "tim.h"


float limitOutput(float output, const float MAX_OUTPUT_ABS){
	output = output > +MAX_OUTPUT_ABS ? +MAX_OUTPUT_ABS : output;
	output = output < -MAX_OUTPUT_ABS ? -MAX_OUTPUT_ABS : output;
	return output;
}


float myabs(float input){
	return input > 0 ? input : -input;
}

// + - represent forward and backward
void runMotorPWMValFB(Motor l_or_r, int16_t pwm_val){
	if(l_or_r == LEFT){ // 具体是左右，需要结合自己的应用场景
		if(pwm_val > 0){ // 逻辑上正转
			// AIN1 和 AIN2的高低电平设置需要和自己应用方向而定，需要做调整
			HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);   
			HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET); 
			__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, myabs(limitOutput(pwm_val,2100)));	// PWM设置需要结合硬件接口
		} else if(pwm_val < 0){
			//BUG
			// AIN1 和 AIN2的高低电平设置需要和自己应用方向而定，需要做调整
			HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);  
			HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
			__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, myabs(limitOutput(pwm_val,2100)));	// PWM设置需要结合硬件接口
		} else { //pwm_val == 0 刹车
			HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);   //AIN1 =  3v3
			HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET); //AIN2 =  3V3
		}
	} else if(l_or_r == RIGHT) {
		// 自行补充,类比推理，照猫画虎
	
	} else {
		return;
	}
}

