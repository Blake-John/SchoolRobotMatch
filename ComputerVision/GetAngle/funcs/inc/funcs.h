#pragma once
#include "process.h"
#include "mathfunc.h"

#define u (double)3
#define focus (double)0.0028


struct d_a
{
    double distance;
    std::vector <double> angle;
};

d_a D_A (cv::Mat img, double true_x, double true_y, cv::Point C, bool to_dilate = 0, int kernel_size = 0);