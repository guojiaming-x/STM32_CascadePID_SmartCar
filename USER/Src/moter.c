#include"moter.h"
#include"main.h"
#include"tim.h"
float limit(float output,const float MAX_OUTPUT_ABS)//限幅
{

	output=output>+MAX_OUTPUT_ABS?+MAX_OUTPUT_ABS:output;
    output=output<-MAX_OUTPUT_ABS?-MAX_OUTPUT_ABS:output;
	return output;
}
float limitOutput(float output,const float MAX_OUTPUT_ABS)//output限幅
{

	output=output>+MAX_OUTPUT_ABS?+MAX_OUTPUT_ABS:output;
	output=output<-MAX_OUTPUT_ABS?-MAX_OUTPUT_ABS:output;
	return output;
}
float myabs(float input)//取绝对值
{
	return input>0?input:-input;
}
void runMotorPWMA(Motor l_or_r, int16_t pwm_val) {
    if (l_or_r == LEFT) { 
        if (pwm_val > 0) { 
            // 逻辑上正转，AIN1 和 AIN2 电平设置根据实际应用方向调整
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
            // PWM 设置结合硬件，limitOutput 限制输出，myabs 取绝对值
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, myabs(limitOutput(pwm_val, 2400))); 
        } else if (pwm_val < 0) { 
            // 逻辑上反转，AIN1 和 AIN2 电平设置根据实际应用方向调整
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, myabs(limitOutput(pwm_val, 2400))); 
        } else { 
            // pwm_val == 0 刹车
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);  
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);  
        }
    } else if (l_or_r == RIGHT) { 
        // 自行补充，类比 LEFT 逻辑，调整 AIN1、AIN2 电平与 PWM 通道等
        if (pwm_val > 0) { 
            // 示例逻辑，需根据实际硬件调整
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, myabs(limitOutput(pwm_val, 2400))); 
        } else if (pwm_val < 0) { 
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, myabs(limitOutput(pwm_val, 2400))); 
        } else { 
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);  
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);  
        }
    } else {
        return;
    }
}
