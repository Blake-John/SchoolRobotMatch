#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <cmath>

double ppD (cv::Point p1, cv::Point p2);
double getDistance1 (cv::Rect boundingrect, double true_x, double true_y, double pixel, double focus);
double getDistance2 (cv::Mat imgWarp, double true_x, double true_y, double pixel, double focus);
std::vector <cv::Point> orderp (std::vector <cv::Point> originp);