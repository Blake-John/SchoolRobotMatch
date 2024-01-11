#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#define log(x) std::cout << x << std::endl;

cv::Mat preprocess (cv::Mat, cv::Mat);
std::vector <cv::Mat> getStandard (cv::Mat, cv::Mat);
std::vector <std::vector <cv::Scalar>> getColorRange (std::vector <cv::Mat>, int);
cv::Rect Aim (cv::Mat, std::vector <cv::Scalar>);