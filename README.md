# STM32 Smart Car — 蓝牙遥控 + 循迹 + 避障

基于 STM32F103C8T6 (HAL库) 的智能小车，完整工程，Keil MDK 直接打开编译。

## 快速开始

用 Keil MDK5 打开 `MDK-ARM/SmartCar.uvprojx` → 编译 → 烧录。

## 功能

- **蓝牙遥控**：E前进/H后退/L左转/R右转/S停止/X旋转
- **5路循迹**：红外传感器阵列，黑线识别
- **超声波避障**：HC-SR04 实时测距
- **双轮差速**：PWM 调速 + GPIO 方向控制

## 文件结构

```
├── SmartCar.ioc              CubeMX工程
├── Core/                     HAL用户代码（gpio/tim/usart初始化）
├── Drivers/                  CMSIS + STM32F1xx HAL库
├── MDK-ARM/                  Keil工程（可直接打开编译）
├── EWARM/                    IAR工程
├── USER/
│   ├── moter.c/h             电机驱动（前进/后退/左转/右转/刹车/旋转）
│   └── interputer_main.c/h   中断服务
├── USER_Moter/
│   └── moter.c/h             电机驱动（另一版本）
└── NUEDC_串级PID参考/         串级PID代码（参考学习）
    ├── User/src/             encoder + pid + motor + interrupt_main
    └── UASER_舵机云台/        X/Y编码器舵机云台模块
```

## 硬件

| 模块 | 引脚 |
|------|------|
| 蓝牙 HC-05 | USART1 |
| 超声波 HC-SR04 | Trig=PB5, Echo=PB4 |
| 5路循迹 | PA3~PA7 |
| 电机 L298N | AIN1/AIN2/BIN1/BIN2 + TIM2 PWM |

---

## 大一项目：智能小车A

`大一项目_智能小车A/` — 大一完成的第一个STM32项目。

- **超声波避障** (`bizhang.c`)：HC-SR04 实时测距
- **5路循迹** (`xunji.c`)：红外传感器阵列，结构体封装 L2/L1/M0/R1/R2
- **蓝牙遥控** (`USART.c`)：串口指令解析
- **电机驱动** (`qudong.c`)：8个运动函数（前进/后退/左转/右转/停止/旋转/左旋/右旋/慢左）
