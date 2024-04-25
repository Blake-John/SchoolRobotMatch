#pragma once
#include "mathfunc.h"

static std::vector <cv::Mat> DilateKernel = {
    cv::getStructuringElement (cv::MORPH_RECT, cv::Size (1, 1)),
    cv::getStructuringElement (cv::MORPH_RECT, cv::Size (2, 2), cv::Point (1, 1)),
    cv::getStructuringElement (cv::MORPH_RECT, cv::Size (3, 3))
};




cv::Mat preprocess (cv::Mat img_in, bool to_dilate = 0, int kernel_size = 0);
std::vector <cv::Point> getTarget (cv::Mat img, cv::Mat imgPre);
cv::Mat warpTarget (cv::Mat img, std::vector <cv::Point> tp, double tx, double ty);