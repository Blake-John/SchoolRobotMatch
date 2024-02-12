#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>


struct Pred
{
    std::vector <cv::Rect> bboxes;
    std::vector <float> confidences;
};

struct Results
{
    std::vector <cv::Rect> bboxes;
    std::vector <float> confidences;
    std::vector <int> classids;
};


struct Result
{
    cv::Rect bbox;
    float confidence;
    int classid;
};



class Yolo
{
private:
    // int w = 640;
    // int h = 640;
    cv::dnn::Net net;
    // int confi_thre;
public:
    Yolo(std::string modelpath);
    cv::Mat forward ();
    Pred getBboxes (cv::Mat output, int width, int height);
    std::vector <cv::Rect> NMS (Pred pred);
    void detect (cv::Mat img, std::vector <cv::Rect> &result);
    void Detect (cv::Mat img, std::vector <Result> &result);
};