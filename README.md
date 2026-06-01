# STM32 Cascade PID Smart Car

串级PID 直流电机位置-速度控制系统，基于 STM32F103 (HAL库)。

## 快速开始

### 1. 用 STM32CubeIDE 打开

```
File → Import → Existing Projects into Workspace
→ 选择本目录 → Finish
```

或双击 `CAR.ioc` → 用 CubeMX 打开 → **GENERATE CODE** → 用 CubeIDE 打开。

### 2. 硬件连接

| 外设 | STM32引脚 | 说明 |
|------|----------|------|
| 编码器 | TIM2 CH1/CH2 | 电机编码器A/B相 |
| 电机PWM | TIM1 CH1 | 左电机PWM |
| 电机方向 | AIN1/AIN2 | GPIO控制正反转 |
| 调试串口 | USART1 | printf输出 |

### 3. 编译烧录

```bash
# CubeIDE内直接点 🔨 Build → ▶ Run
```

## 系统架构

```
目标角度(720°) ──→ [位置环 P] ──→ [速度环 PI] ──→ 电机 PWM
                      ↑                   ↑
                 编码器角度反馈        编码器速度反馈
```

**TIM3 10ms中断中执行的串级控制：**
```
updateEncoder() → 位置环PID → 速度环PID → runMotorPWM()
```

## 文件结构

```
├── CAR.ioc                    CubeMX工程（引脚/时钟/外设配置）
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── encoder.h          编码器数据结构
│   │   ├── pid.h              PID控制器结构体
│   │   ├── motor.h            电机接口
│   │   └── interrupt_main.h   控制初始化声明
│   └── Src/
│       ├── main.c             主入口
│       ├── encoder.c          编码器驱动（16/32位自适应溢出补偿）
│       ├── pid.c              标准位置式PID
│       ├── motor.c            直流有刷电机PWM驱动
│       └── interrupt_main.c   串级PID控制循环
└── Drivers/                   （CubeMX生成，首次打开.ioc自动创建）
```

## 核心实现

### 编码器 (`encoder.c`)

自动适配16/32位定时器，跳变阈值检测溢出方向并补偿，物理量解算：
```
原始脉冲 → 转数 → 角度 → 距离 → 线速度
```

参数：4倍频 × 减速比30:1 × 500线编码器 × 轮半径0.065m

### 串级PID参数

| 环 | 类型 | Kp | Ki | Kd | 输出限幅 |
|----|------|-----|-----|-----|----------|
| 位置环(外环) | P | 0.9 | 0 | 0 | ±300 RPM |
| 速度环(内环) | PI | 10 | 0.5 | 0 | ±2100 PWM |

### 电机驱动 (`motor.c`)

- 正转：AIN1=LOW, AIN2=HIGH
- 反转：AIN1=HIGH, AIN2=LOW
- 刹车：AIN1=AIN2=HIGH（电机制动）
