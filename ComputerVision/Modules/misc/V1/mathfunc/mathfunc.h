#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

void getStandard (std::vector <cv::Rect> &origin, std::vector <cv::Rect> &ordered);
void Aim (cv::Mat img, std::vector <cv::Rect> standard, int aimkey);
