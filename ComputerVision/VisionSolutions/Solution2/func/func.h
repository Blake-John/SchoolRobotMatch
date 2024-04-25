#pragma once

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "yolo.h"

#define log(x) std::cout << x << std::endl;

cv::Mat preprocess (cv::Mat img_in, cv::Scalar lower, cv::Scalar upper);
cv::Rect gettarget (cv::Mat imgMask);
void drawresult (cv::Mat img, std::vector <std::vector <Result>> target);
int getlaser (cv::Mat img, cv::Scalar laser_upper, cv::Scalar laser_lower, cv::Rect laser);
void order (std::vector <Result> &result, std::vector <std::vector <Result>> &target);
