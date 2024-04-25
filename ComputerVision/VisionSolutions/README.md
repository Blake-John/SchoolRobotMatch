# 01 简介

本项目是基于 `OpenCV` 和 `C++` 小车视觉识别程序，主要包含3种 `Solution` 。

# 02 开发环境

* System - Arch / Ubuntu
* Language - C++ / Python
* Libararies - OpenCV-4.9.0
* 杰锐微通相机 -  DF100 720P 2.8mm

# 03 目录结构

```
.
├── README.md
├── Solution1          # 基于 Yolo 的静态瞄准
├── Solution2          # 基于 Yolo 的动态瞄准
├── Solution3          # 基于传统视觉的瞄准
├── test.py
└── TODO.md
```

# 04 功能说明

## 4.1 目标检测

1. `Solution1` 和 `Solution2` 通过 `dnn` 模块加载 `Yolo to ONNX` 模型，并通过推理来获取目标的位置信息
2. `Solution3` 通过传统的视觉方法来检测并获取目标的位置信息

## 4.2 通信

三个解决方案皆通过操控 `Linux` 系统下 `ttyUSB0` 文件来操控串口的行为。电脑通过 `usb2ttl` 模块和单片机相连，并又程序向串口文件中写入数据，从而实现数据的传输。

## 4.3 瞄准

1. `Solution1` 通过计算激光位置与目标位置之间的偏角，一次性获取激光偏转的角度
2. `Solution2` 和 `Solution3` 通过实时获取激光的位置，并通过动态调整偏转的角度，从而实现动态瞄准

# 05 使用

三个方案均在 `Linux` 系统下通过 `C++` 开发，需要通过 `cmake` 和 `make` 来编译程序
