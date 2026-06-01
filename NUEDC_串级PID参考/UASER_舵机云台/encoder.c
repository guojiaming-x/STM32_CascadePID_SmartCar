#include"main.h"
#include "tim.h"
#include "encoder.h"
#include "servor.h"

void encoder_Init(void)
{
  HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	 __HAL_TIM_SET_COUNTER(&htim4,90);
	 __HAL_TIM_SET_COUNTER(&htim2,90);
}
void encoder_updata(void)
{
    //±àÂëÆ÷Ò»
	
	  encoder_count[0]=__HAL_TIM_GET_COUNTER(&htim4)*1;//Y
	  if(encoder_count[0]>=180.0)
	  {  __HAL_TIM_SET_COUNTER(&htim4,180);}
	    if(encoder_count[0]==65535)
	  {  __HAL_TIM_SET_COUNTER(&htim4,0);}
	 
	//±àÂëÆ÷¶þ
	   encoder_count[1]=__HAL_TIM_GET_COUNTER(&htim2)*1;//X
	  if(encoder_count[1]>=180.0)
	  {  __HAL_TIM_SET_COUNTER(&htim2, 180);}
	    if(encoder_count[1]==65535)
	  {  __HAL_TIM_SET_COUNTER(&htim2,0);}
	  

}
 



