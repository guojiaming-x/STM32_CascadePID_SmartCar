#ifndef __ENCODER_H
#define __ENCODER_H

#include "stdint.h"
#include "tim.h"

// !!!!!此文件仅适用于用STM32 PWM驱动的带有GMR(光电)or霍尔编码器的直流电机!!!!

typedef struct {
	uint8_t  multiple;			// x倍频 可取2 or 4，对应cubemx的配置
	float 	 reduction_ratio;	// 电机减速比，例如最常见的 30
	uint16_t ppr;				// 编码器线数，GMR编码器:500 霍尔编码器:13
	float	 r;					// 轮子半径,例如0.0123 m, 单位 m
	TIM_HandleTypeDef* tim_hander; // 用于编码器读取AB相进行编码的指针
}Parameter;

//P.S. 速度基本上不可能越过float的表示范围  光速也就才3*10^8
typedef struct{ 	
	float angular;		//角速度，单位rpm
	float linear;		//线速度，单位m/s
} Velocity;

typedef struct{
	double rotations;	//电机输出轴转动圈数和	无单位
	double distance;	//轮子前进or后退距离	单位:m
	double angle;		//轮子正传or反转角度	单位:°
} Position;

typedef struct{
	uint32_t count_now;			//编码器当前计数
	uint32_t count_last;		//编码器上次计数
	int64_t  count_increment;	//编码器两帧增量计数, must int64 .+表示正转 -表示反方向转
	int64_t  count_total;		//编码器总计数
	
	int64_t  count_overflow;	//计数器寄存器 TIMx_CNT溢出次数
								//-正数表示-正传上溢出
								//-负数表示-反转下溢出
	int32_t  JUMP_THRESHOLD;		//计数器溢出阈值
	uint32_t TIMx_MAX_COUNT;	//16bits-TIMx: 2^16 - 1   32bits-TIMx: 2^32 - 1
} Counter;

typedef enum{
	UP = 0,
	DOWN = 1,
	INIT = 2
}Direction;

typedef struct{
	Parameter param;
	
	Direction direction;
	
	Velocity velocity;
	
	Position position;
	
	Counter counter;
}Encoder;


void initEncoder(Encoder* ecd, const Parameter param);
void updateEncoderLoopSimpleVersion(Encoder* ecd, uint16_t loop_period);
void updateEncoderLoopOverflowVersion(Encoder* ecd, uint16_t loop_period);





#endif /* __ENCODER_H */

