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