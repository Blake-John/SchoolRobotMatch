#pragma once

#include "func.h"
#include "serial.h"

void aimming (cv::VideoCapture cap, std::vector <Result> target, int num, cv::Scalar laser_lower, cv::Scalar laser_upper, int fd);
int daimming (int fd, cv::VideoCapture cap, cv::Rect target, cv::Scalar laser_lower, cv::Scalar laser_upper);
void waitfor (cv::VideoCapture cap);

