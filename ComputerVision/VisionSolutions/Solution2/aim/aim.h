#pragma once

#include "yolo.h"
#include "func.h"
#include "serial.h"

void aimming (cv::Mat img, std::vector <Result> target, int num, cv::Scalar lower, cv::Scalar upper);
int daimming (int fd, cv::VideoCapture cap, cv::Rect target, cv::Scalar lower, cv::Scalar upper);
void waitfor (cv::VideoCapture cap);