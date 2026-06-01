/* USER CODE BEGIN Includes */
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
/* USER CODE END Includes */

Encoder ecd;
PID vec_left;   // 速度环
PID pos_left;   // 位置环

// 在 main.c 中声明（来自 interrupt_main.h）
extern void myCarControlCodeInit(void);

/* USER CODE BEGIN 2 */
  myCarControlCodeInit();
/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
  while (1)
  {
    // 主控逻辑在 TIM3 中断中执行（见 interrupt_main.c）
  }
/* USER CODE END WHILE */
