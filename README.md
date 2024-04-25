# RobotMatch

该仓库用于存放华工机器人校内赛的各种 **代码，文件，资料** 等其中，主要分为

* `ComputerVisioin` 
* `Microccontroller` 
* `MechanicalStructure` 

三个板块，其中

* `ComputerVision` 用于存放视觉识别的相关代码，模型等
* `Microcontroller` 用于存放电控的相关代码，电路板设计等资料
* `MechanicalStructure` 用于存放小车的结构，模型等

> 详细更新信息请阅读 [CHANGELOG](CHANGELOG.md)


## 1. ComputerVisioin

### 1.0 Structure

```
.
├── Modules                        # 一些模块
├── MidTermAssessment              # 中期考核程序
├── debugging                      # 存放用于赛前赛时调试用的程序
└── VisionSolutions                # 比赛瞄准项目
```

### 1.1 Modules

存放这一些准备比赛时使用的模块，较为杂

### 1.2 MidTermAssessment

用于提交 **中期考核** ，代码效果展示见 [Video](./ComputerVision/MidTermAssessment/medias/1.mkv)

详情可见 [MidTermAssessment](./ComputerVision/MidTermAssessment/README.md) 以及 [What to do](./ComputerVision/MidTermAssessment/TODO.md)

### 1.3 debugging

关于该目录可见 [debugging](./ComputerVision/debugging/README.md) 以及 [what to do](./ComputerVision/debugging/TODO.md)

### 1.4 VisionSolutions

视觉方面的项目目录，存放了用于比赛瞄准的程序，可见 [VisionSolutions](./ComputerVision/VisionSolutions/README.md) 以及 [What to do](./ComputerVision/VisionSolutions/TODO.md)

## 2. MicroController

### 2.0 Structure

```
.
├── MajorControl_Source            # 比赛小车控制项目
├── PID速度环控制
├── RemoteController_nRF20L01      # 控制手柄
├── SerialControl                  # 串口通信代码
├── SerialMCU
└── SerialPWM
```

### 2.1 SerialControl

串口通信模块，实现在 Linux 系统下，通过 C++ 程序与 STM32 通信

### 2.2 SerialMCU

接受信息模块，将接受到的特定数据包在OLED上显示

### 2.3 SerialPWM

接受信息，并控制舵机旋转

### 2.4 RemoteController_nRF20L01

控制手柄的pcb项目

### 2.5 MajorControl_Source

电控的 PCB 板源文件， `ZET6` 主控板源代码， `C8T6`从控板源代码以及遥控手柄控制源码。

实现了通过手柄上的 2.4G 模块向 `ZET6` 主控板发送信息，从而驱动小车，并实现比赛所需要的捡球，上高台，兑换等功能

详细信息可见 [MajorControl_Source-README](./MicroController/MajorControl_Source/README.md)

## 3. MechanicalStructure
### 3.1 零件

小车结构的零件，包括小车的 **基本框架** ，**麦轮结构**，**扫球装置**，**tt130电机**

### 3.2 装配体

小车结构的装配体，包括 **局部装配体** 以及 **整车装配体**

![Total](MechanicalStructure/imgs/整车装配.png)

### 3.3 Mearm机械臂

机械臂的结构，包括各 **部位零件** 及 **装配体**

![Arm](MechanicalStructure/imgs/机械臂装配.png)
