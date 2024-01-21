#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

#define log(x) std::cout << x << std::endl;
#define PI 3.1415926;

double ppD (cv::Point p1, cv::Point p2);
std::vector <cv::Point> orderp (std::vector <cv::Point> originp);
cv::Point getCenter (std::vector <cv::Point> points);
double getDistance (cv::Mat imgWarp, double true_x, double true_y, double u, double d);
std::vector <double> TrueDeflection (cv::Mat imgWarp, double dx, double dy, double true_x, double true_y);
std::vector <double> getAngle1 (double distance, double true_dx, double true_dy);
std::vector <double> getAngle2 (double dx, double dy, double u, double d);