#include "qudong.h"
#include "gpio.h"
#include "main.h"
#include "tim.h"
void goForward(void)
{
    // 左轮
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
    // 右轮
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,900);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,900);
}
void goBack(void)
{
	// 左轮
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
    // 右轮
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,900);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,900);
}
void goLeft(void)
{
    // 左轮
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
    // 右轮
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,900);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,900);
}
void goRight(void)
{// 左轮
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
    // 右轮
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
    // 左轮
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,900);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,900);
}
void stop(void)
{
	// 左轮
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
    // 右轮
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,900);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,900);
}
void xuanzhuang(void)
{

    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,900);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,900);
}
void zuozuan(void){

   HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
    // 右轮
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,100);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,500);


}
void youzuan(void )
{
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
    // 右轮
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,500);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,100);
}

void manzuo(void)
{
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
    // 右轮
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,500);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,500);

}
