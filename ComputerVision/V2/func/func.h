#pragma once

#include <opencv2/opencv.hpp>
#include "yolov3.h"

void order (std::vector <Result> &result, std::vector <std::vector <Result>> &target);
std::vector <double> getAngle (double dx, double dy, double u, double d);
