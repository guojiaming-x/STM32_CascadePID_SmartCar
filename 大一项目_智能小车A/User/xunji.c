
#include"main.h"
#include "stdint.h"
#include "qudong.h"
#define TRACE_L2_PIN  GPIO_PIN_3
#define TRACE_L1_PIN  GPIO_PIN_4
#define TRACE_M0_PIN  GPIO_PIN_5
#define TRACE_R1_PIN  GPIO_PIN_6
#define TRACE_R2_PIN  GPIO_PIN_7
#define TRACE_GPIO    GPIOA


uint8_t Read_TraceSensor(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}


typedef struct {
    uint8_t L2;
    uint8_t L1;
    uint8_t M0;
    uint8_t R1;
    uint8_t R2;
}A;
A sensor;
void xunjimode(A*sensor) {
    sensor->L2 = Read_TraceSensor(TRACE_GPIO, TRACE_L2_PIN);
    sensor->L1 = Read_TraceSensor(TRACE_GPIO, TRACE_L1_PIN);
    sensor->M0 = Read_TraceSensor(TRACE_GPIO, TRACE_M0_PIN);
    sensor->R1 = Read_TraceSensor(TRACE_GPIO, TRACE_R1_PIN);
    sensor->R2 = Read_TraceSensor(TRACE_GPIO, TRACE_R2_PIN);
	if(sensor->M0==1&&sensor->L1==0&&sensor->R1==0)
	{
	goForward();
	}
	else if(sensor->L1==1&&sensor->L2==0)
	{
	goLeft();
	}
	else if(sensor->R1==1&&sensor->R2==0)
	{
	goRight();
	}
	
	
}