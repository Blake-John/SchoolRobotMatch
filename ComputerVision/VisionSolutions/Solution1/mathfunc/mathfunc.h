#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include "yolo.h"

#define PI (double)3.1415926
#define u (double)3 // 相机像素元尺寸
#define focus (double)0.0028
#define d (double)0.0031945 // 相机成像平面到镜头的距离
#define C cv::Point (640, 360) // 相机画面中心点

std::vector <double> YawPitch (cv::Point pt1, cv::Point pt2);
void order (std::vector <Result> &result, std::vector <std::vector <Result>> &target);
// std::vector <double> RollPitch (cv::Point pt1, cv::Point pt2);