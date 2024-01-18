#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

cv::Mat preprocess (cv::Mat);
cv::Rect getTarget1 (cv::Mat img, cv::Mat imgPre);
std::vector <cv::Point> getTarget2 (cv::Mat img, cv::Mat imgPre);
cv::Mat warpTarget1 (cv::Mat img, std::vector <cv::Point> tp, double tx, double ty);
cv::Mat warpTarget (cv::Mat img, std::vector <cv::Point> tp, double tx, double ty);