#include "servor.h"
#include "main.h"
#include "stdlib.h"
#include "tim.h"

//#define ANGLE_TOLERANCE 1       // 0.01°容差
//#define MOVE_STEP_MAX   200     // 最大单步变化量
//#define PWM_MIN         500     // 0°对应脉冲
//#define PWM_MAX         2500    // 180°对应脉冲
//// 双轴控制系统
//typedef struct {
//    int32_t current;     // 当前角度 0.01°
//    int32_t target;      // 目标角度 0.01°
//    uint32_t tim_ch;     // 定时器通道
//} XY;

//  XY axes[2] = {
//    {9000, 9000, TIM_CHANNEL_1}, // X轴 (0-18000对应0.00-180.00°)
//    {9000, 9000, TIM_CHANNEL_2}  // Y轴
//};


 uint32_t Angleturn(double angle) //PWM 转角度
{
     //angle = angle < 0 ? 0 : (angle > 180.0 ? 180.0 : angle);  
    return (uint32_t)( 500+(angle / 180.0) * 2000); 
}
void servo_get(float X,float Y)
{
TIM1->CCR1=Angleturn(X);
TIM1->CCR2=Angleturn(Y);


}

//uint32_t AngleToPulse(int32_t angle_int) // 整数乘除，避免浮点运算，角度控制
//{
//    angle_int = angle_int < 0 ? 0 : (angle_int > 18000 ? 18000 : angle_int);
//    return 500 + (angle_int * 2000) / 18000;  
//	//0-180.00   500-2500   0-1800
//}


//void point()//原点复位
//{
//    axes[0].target = 9000; // X轴目标,接线单片机左
//    axes[1].target = 9000; // Y轴目标，接线单片机右

//    __HAL_TIM_SET_COMPARE(&htim3, axes[0].tim_ch, AngleToPulse(9000));
//    __HAL_TIM_SET_COMPARE(&htim3, axes[1].tim_ch, AngleToPulse(9000));
//    // 重置当前角度
//    axes[0].current = 9000;
//    axes[1].current = 9000;
//	
//	
//	
//}

////void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
////    if (htim->Instance == TIM4) {
////        uint8_t arrived = 1;
////        
////        for (int i = 0; i < 2; i++) {
////            int32_t error = axes[i].target - axes[i].current;
////            
////            if (abs(error) > ANGLE_TOLERANCE) {
////                arrived = 0;
////                // 动态步长控制
////                int32_t step = error / 10;  // 比例因子
////                step = step > MOVE_STEP_MAX ? MOVE_STEP_MAX : 
////                      (step < -MOVE_STEP_MAX ? -MOVE_STEP_MAX : step);
////                
////                axes[i].current += step;
////                // 更新PWM输出
////                __HAL_TIM_SET_COMPARE(&htim3, axes[i].tim_ch, AngleToPulse(axes[i].current));
////            }
////        }
////        
////        // 全部轴到位后停止定时器
////        if (arrived) HAL_TIM_Base_Stop_IT(&htim4);
////    }
////}




////void Set_TargetX(float x_cm, float y_cm) //转角度控制
////	{
////		axes[0].
//// 
////    HAL_TIM_Base_Start_IT(&htim4);
////    }


















