# RobotMatch

该仓库用于存放华工机器人校内赛的各种 **代码，文件，资料** 等其中，主要分为

* `ComputerVisioin` 
* `Microccontroller` 
* `MechanicalStructure` 

三个板块，其中

* `ComputerVision` 用于存放视觉识别的相关代码，模型等
* `Microcontroller` 用于存放电控的相关代码，电路板设计等资料
* `MechanicalStructure` 用于存放小车的结构，模型等

> 详细信息请阅读 [CHANGELOG](CHANGELOG.md)

## 1. ComputerVision
### 1.1 AutoAimming

用于比赛时视觉方面 **获取目标** 以及 **瞄准顺序**

### 1.2 GetDistance

用于中期考核以及瞄准用的 **距离测量**

### 1.3 GetAngle

用于瞄准的 **偏角** 计算模块

### 1.4 Calibration

用于测量相机的 **相距**

> `param.csv` 用于存放相机的各种参数

### 1.5 `Aim` 

用于更加准确地获得 **目标色块**

## 2. MicroController
### 2.1 SerialControl

串口通信模块，实现在 Linux 系统下，通过 C++ 程序与 STM32 通信

### 2.2 SerialMCU

接受信息模块，将接受到的特定数据包在OLED上显示

### 2.3 SerialPWM

接受信息，并控制舵机旋转