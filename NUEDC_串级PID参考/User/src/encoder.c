#include "encoder.h"
#include "limits.h"
#define PI 3.14159265358979323846

void initEncoder(Encoder* ecd, const Parameter param)
{
	ecd->param = param;
	
	// 初始化速度
    ecd->velocity.angular = 0;
    ecd->velocity.linear = 0;
	
	// 初始化位置
    ecd->position.rotations = 0;
    ecd->position.distance = 0;
    ecd->position.angle = 0;

    // 初始化计数器
	ecd->counter.count_now = 0;
    ecd->counter.count_last = 0;
	ecd->counter.count_increment = 0;
    ecd->counter.count_total = 0;
	
	ecd->counter.count_overflow = 0;
	// 可以计算一下,最大转速旋转对应的计数值，这里就取个折中的数，可能需要根据实际电机和情况而修正
    ecd->counter.JUMP_THRESHOLD = 30000;  // 这里将阈值设置为30000，你可以根据需求进行调整
	ecd->counter.TIMx_MAX_COUNT = 0;	  // 在循环中判断最大是多少 
	
	ecd->direction = INIT;
}




void updateEncoderLoopSimpleVersion(Encoder* ecd, uint16_t loop_period){
	// direction
	ecd->direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(ecd->param.tim_hander);
	
	//-----counter
	// counter_now
	ecd->counter.count_now = __HAL_TIM_GET_COUNTER(ecd->param.tim_hander);
	
	// counter_increament 
	ecd->counter.count_increment = (int64_t)((int16_t)(ecd->counter.count_now - 0));
	
	// counter_total
	ecd->counter.count_total += ecd->counter.count_increment;
	
	//-----position
	ecd->position.rotations = (double)ecd->counter.count_total / ((double)ecd->param.multiple * ecd->param.reduction_ratio * (double)ecd->param.ppr);
    ecd->position.angle = ecd->position.rotations * 360.0;
	ecd->position.distance = ecd->position.rotations / 60.0 * PI * 2.0 * ecd->param.r;
	
	//-----velocity
	ecd->velocity.angular = (float)(ecd->counter.count_increment/((float)ecd->param.multiple * ecd->param.reduction_ratio * (float)ecd->param.ppr) * 1000.0 / loop_period * 60);
	ecd->velocity.linear = (float)(ecd->velocity.angular/60.0 * PI * 2.0 * ecd->param.r);
	
	// 清空 CNT计数器
	__HAL_TIM_SetCounter(ecd->param.tim_hander, 0 );
}


void updateEncoderLoopOverflowVersion(Encoder* ecd, uint16_t loop_period){
	ecd->direction = (Direction)__HAL_TIM_IS_TIM_COUNTING_DOWN(ecd->param.tim_hander);
	ecd->counter.count_now = __HAL_TIM_GET_COUNTER(ecd->param.tim_hander);
	// bug1
	ecd->counter.count_increment = (int64_t)ecd->counter.count_now - (int64_t)ecd->counter.count_last;
	
	// 是否上溢or下溢
	// overflow detection and compensate
	// down overflow
	if(ecd->counter.count_increment > ecd->counter.JUMP_THRESHOLD){
		ecd->counter.count_overflow --;		
		
		//判断16bits or 32bits
		// 5.1.1 32bits TIMx
		if(ecd->counter.count_last > USHRT_MAX || ecd->counter.count_now > USHRT_MAX){ // USRT_MAX = 65535 2^16-1
			ecd->counter.TIMx_MAX_COUNT =  UINT_MAX;  //2^32 - 1 #include "limits.h" 
		} else { // 5.1.2 16bits TIMx
			ecd->counter.TIMx_MAX_COUNT =  USHRT_MAX; //2^16 - 1 #include "limits.h" 
		}
		
		
		//compensate -(TIMx_MAX_COUNT+1)
		ecd->counter.count_increment = ecd->counter.count_increment - ecd->counter.TIMx_MAX_COUNT - 1;
	} else if(ecd->counter.count_increment < -ecd->counter.JUMP_THRESHOLD){
		// up overflow
		ecd->counter.count_overflow ++; 
		
		//判断16bits or 32bits
		// 5.1.1 32bits TIMx
		if(ecd->counter.count_last > USHRT_MAX || ecd->counter.count_now > USHRT_MAX){ // USRT_MAX = 65535 2^16-1
			ecd->counter.TIMx_MAX_COUNT =  UINT_MAX;  //2^32 - 1 #include "limits.h" 
		} else { // 5.1.2 16bits TIMx
			ecd->counter.TIMx_MAX_COUNT =  USHRT_MAX; //2^16 - 1 #include "limits.h" 
		}
		
		//compensate +(TIMx_MAX_COUNT+1) 
		ecd->counter.count_increment = ecd->counter.count_increment + ecd->counter.TIMx_MAX_COUNT + 1;
	}
	
	
	// 下面的和之前的就一样了
	ecd->counter.count_total += ecd->counter.count_increment;
	ecd->position.rotations = (double)ecd->counter.count_total / (double)(ecd->param.multiple * ecd->param.reduction_ratio * ecd->param.ppr);
	ecd->position.angle = ecd->position.rotations * 360.0;
	ecd->position.distance = ecd->position.rotations / 60.0 * PI * 2 * ecd->param.r;
	ecd->velocity.angular = (double)ecd->counter.count_increment / (double)(ecd->param.multiple * ecd->param.reduction_ratio * ecd->param.ppr) * 1000.0 / loop_period * 60;
	ecd->velocity.linear = ecd->velocity.angular/60.0 * PI * 2.0 * ecd->param.r;

	ecd->counter.count_last = ecd->counter.count_now;
}



