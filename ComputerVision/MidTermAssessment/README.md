# 视觉中期考核

此次完成的是视觉组的中期考核

* 题目一、三、四的展示视频见 [Video1](videos/1.mkv)
* 题目二没有专门录制，但是可以见 [Video2](videos/2.mp4)

所有代码都上传至 [仓库](https://gitee.com/blake-john/robot-match/tree/master/ComputerVision/MidTermAssessment) 中，可以通过以下命令查看

```bash
git clone https://gitee.com/blake-john/robot-match.git
```

## 01 基本说明

这次中期考核的代码由两个基本模块 `mathfunc` 和 `yolo` 组成。项目中

* `mathfunc` 是用于 **bbox排序**、 **计算偏角** 的模块
* `yolo` 适用于调用网络模型进行 **推理** 的模块
* `model/` 存放用于推理的 **onnx 模型**
* `videos/` 存放 **展示视频**
* `imgs/` 存放 **测试用的图片**

## 02  `mathfunc` 

该模块用于存放基本 **数学方法** 以及 **与相机有关的宏定义**、

### `YawPitch` 

使用最基本的 **几何方法** 计算欧拉角中的 **`Yaw` 偏航角** 以及 **`Pitch` 俯仰角**。

我看到群里有人使用 `PnP` 来计算坐标，但是在实际比赛的时候，难以确定已知的点用于解算，或者说误差应该不小，还有最最重要的是 **我不会！！！QwQ T-T :(**

### `order`

通过 $x, y$ 坐标 选出上方的五个标准区色块

## 03 `yolo`

使用 `yolov3` 的 `yolov3-tiny.pt` 预训练模型进行训练，然后导出为 `onnx` 模型，利用opencv中的 `dnn` 模块加载模型并进行推理

对于该模块，我将网络的初始化及推理 **封装成一个 `Yolo` 类** ，并通过接收 **模型所在路径** 作为参数来初始化该类。接着在类中定义了推理的方法，但是为了 **减少资源的开销**，我将推理过程全都写在 `Detect` 方法中，大致思路为：**设置输入**，**前向推理**，**通过置信度过滤bbox**，**使用NMS获取最终目标的bbox**。

至于为什么不用传统的 **边缘检测以及HSV色域**，是因为我我手搓的那块板太烂了，而且在家里拍出来的照片背景一堆，再加上不知到时候比赛现场的环境怎么样，于是就选了用神经网络来识别。

> 代码的讲解可见代码本身的注释，或者仓库中的 [CHANGELOG.md](https://gitee.com/blake-john/robot-match/blob/master/CHANGELOG.md)