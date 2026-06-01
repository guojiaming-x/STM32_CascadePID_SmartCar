#include"tim.h"
#include"stdio.h"
#include"moter.h"
//-Encoder
int16_t counter_now=0;
int64_t counter_total=0;
float rotation=0;
float velocity_w=0;

//-PID
//pid公式
//output=kp*error_now + ki*error_integral+ kd*(error_now-error_last);

//--PID-only kp-begin
//1-PID parameter
float I_MA=5000;//积分限辐
float kp=10;
float ki=0.1;
float kd=0;
const float MAX_OUTPUT=2400;
//2-PID target
float target_w=200;//rpm
//3-PID error
float error_now=0;  
float error_integral=0;
float error_last=0;
//4—output
float output=0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
	 if(htim==&htim3)
	 {
		 
	
	  //-Encoder
		 counter_now=(int16_t)__HAL_TIM_GET_COUNTER(&htim2);
		 counter_total+=counter_now;
		 rotation=(float)counter_total/(21.3*11*4);//ppr*减速比*4（上升沿下降沿计数）
		 velocity_w=(float)counter_now/(21.3*11*4)*1000.0/10.0*60.0;
	
		__HAL_TIM_SetCounter(&htim2,0);
		// printf("%.1f,%.1f\n",rotation,velocity_w);
	  //-PID-only KP+KI
		 error_now=target_w-velocity_w;
		 error_integral+=error_now;
		 output=kp*error_now+ki*error_integral+kd*(error_now-error_last);
		 error_last=error_now;
		 output=limit(output,MAX_OUTPUT);
		 
		 
		 printf("PID:%.2f,%.2f,%.2f\n",target_w,velocity_w,output);
		 runMotorPWMA(LEFT,output);
	  //只用P控制到达目标值迅速到电，然后产生误差，再到达目标值，循环往复，产生稳态误差
		 
	 }
 }
 