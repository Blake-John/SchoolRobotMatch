#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

// struct Pred
// {
//     std::vector <cv::Rect> bboxes;
//     std::vector <float> confidences;
// };

// struct Results
// {
//     std::vector <cv::Rect> bboxes;
//     std::vector <float> confidences;
//     std::vector <int> classids;
// };


/**
 * @brief 用于存储网络推理检测结果的结构体
 * @param bbox 矩形框，目标所在矩形
 * @param confidence 矩形框的置信度
 * @param classid 分数最高的分类id，所有分类见 @ref `Classes`
 */
struct Result
{
    cv::Rect bbox;
    float confidence;
    int classid;
};


/**
 * @class Yolo
 * @brief 用于实现通过 `dnn` 模块加载 `onnx` 模型来推理，从而获得目标及起位置信息
 *
 * @method Yolo 通过传模型路径来初始化网络
 * @method Detect 通过传入目标图片来推理，并将推理结果放置于一个存储单个结果的向量中
 *
 * @attr net 加载的网络模型
 *
 */
class Yolo
{
private:
    cv::dnn::Net net;
    // int w = 640;
    // int h = 640;
    // int confi_thre;
public:
    Yolo(std::string modelpath);
    void Detect (cv::Mat img, std::vector <Result> &result);
    // cv::Mat forward ();
    // Pred getBboxes (cv::Mat output, int width, int height);
    // std::vector <cv::Rect> NMS (Pred pred);
    // void detect (cv::Mat img, std::vector <cv::Rect> &result);
};
