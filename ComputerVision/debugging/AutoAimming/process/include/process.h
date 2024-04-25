#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#define log(x) std::cout << x << std::endl;

cv::Mat preprocess (cv::Mat img_in);
std::vector <cv::Mat> getStandard (cv::Mat img_pre, cv::Mat img);
std::vector <std::vector <cv::Scalar>> getColorRange (std::vector <cv::Mat> myStandard, int threshold);
cv::Rect Aim (cv::Mat img, std::vector <cv::Scalar> colorrange);
