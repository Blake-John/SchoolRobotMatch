#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

struct DetectResult
{
    int classid;
    float confi;
    cv::Rect bbox;
};

class YoloV5Detector
{
private:
    int input_w = 640;
    int input_h = 640;
    cv::dnn::Net net;
    int score_thre = 0.25;
public:
    YoloV5Detector(std::string onnxpath);
    void detect (cv::Mat frame, std::vector <DetectResult> &result);
    void draw (cv::Mat img, std::vector <DetectResult> res);

};