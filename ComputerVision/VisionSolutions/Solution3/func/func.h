#pragma once

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

#define log(x) std::cout << x << std::endl;

/**
 * @class Result
 * @brief 用于存放目标信息的结构体
 *
 */
struct Result
{
	cv::Rect bbox;
	int classid;
};

std::vector <Result> gettarget (cv::Mat img, std::vector <std::vector <int>> colorranges);
void drawresult (cv::Mat img, std::vector <Result> piece_results);
int getlaser (cv::Mat img, cv::Scalar laser_upper, cv::Scalar laser_lower, cv::Rect laser);
void order (std::vector <Result> &result, std::vector <Result> &target);

