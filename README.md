# STM32 Cascade PID Smart Car

串级PID 直流电机位置-速度控制系统，基于 STM32F103 (HAL库)。

## 系统架构

```
目标角度(720°) ──→ [位置环 P] ──→ [速度环 PI] ──→ 电机 PWM
                      ↑                   ↑
                 编码器角度反馈        编码器速度反馈
```

**10ms 定时中断中执行的串级控制：**

1. `updateEncoder()` — 读取编码器，计算当前位置和速度
2. 位置环 `updatePID()` — 输入当前角度，追踪目标 720°
3. 位置环输出 → 速度环目标
4. 速度环 `updatePID()` — 输入当前角速度
5. 速度环输出 → `runMotorPWMValFB()` → 电机

## 文件结构

```
User/
├── inc/
│   ├── encoder.h         编码器数据结构定义
│   ├── pid.h             PID 控制器结构体定义
│   ├── motor.h           电机接口定义
│   └── interrupt_main.h  控制初始化函数声明
├── src/
│   ├── encoder.c         编码器驱动（含16/32位自适应溢出补偿）
│   ├── pid.c             标准位置式 PID 控制器
│   ├── motor.c           直流有刷电机 PWM 驱动（正转/反转/刹车）
│   └── interrupt_main.c  串级 PID 控制主循环
└── CAR.ioc              STM32CubeMX 工程文件
```

## 核心实现

### 编码器 (`encoder.c`)

- 支持 16 位和 32 位定时器自动适配
- 跳变阈值检测（JUMP_THRESHOLD=30000）识别溢出方向
- 自动补偿上溢/下溢，确保长时间运行不丢步
- 物理量解算：原始脉冲 → 转数 → 角度 → 距离 → 线速度

### PID 控制器 (`pid.c`)

```
error = target - input
integral += error                        // 积分累加（带限幅）
output = Kp×error + Ki×integral + Kd×(error - last_error)
output = limit(output, ±MAX_OUTPUT)      // 输出限幅
```

### 串级控制参数

| 环 | 类型 | Kp | Ki | Kd | 输出限幅 |
|----|------|-----|-----|-----|----------|
| 位置环(外环) | P | 0.9 | 0 | 0 | ±300 RPM |
| 速度环(内环) | PI | 10 | 0.5 | 0 | ±2100 PWM |

### 电机驱动 (`motor.c`)

- 正转：AIN1=LOW, AIN2=HIGH
- 反转：AIN1=HIGH, AIN2=LOW
- 刹车：AIN1=HIGH, AIN2=HIGH

## 硬件需求

- STM32F103 系列 MCU
- 带编码器的直流减速电机（500线，30:1 减速比，4倍频，轮半径 0.065m）
- TB6612 / L298N 电机驱动模块

## 编译

用 STM32CubeIDE 打开 `CAR.ioc`，生成代码后将 `User/` 目录下的文件放入对应位置即可编译。
