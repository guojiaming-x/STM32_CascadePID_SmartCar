#include "main.h"
#include "tim.h"
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

 void xunjimode() {
    uint8_t L2, L1, M0, R1, R2;
    
    L2 = Read_TraceSensor(TRACE_GPIO, TRACE_L2_PIN);
    L1 = Read_TraceSensor(TRACE_GPIO, TRACE_L1_PIN);
    M0 = Read_TraceSensor(TRACE_GPIO, TRACE_M0_PIN);
    R1 = Read_TraceSensor(TRACE_GPIO, TRACE_R1_PIN);
    R2 = Read_TraceSensor(TRACE_GPIO, TRACE_R2_PIN);
 if (M0 == 0 && L1 == 1&& R1 == 1)
	{
        
	    manzuo();
	
    } 
 
    else if (L1 ==0  || L2 == 0) {
  
		zuozuan();

    } 

    else if (R1 == 0 || R2 == 0) {
      
		youzuan();
    } 

   
    else {
    manzuo();
    }
}