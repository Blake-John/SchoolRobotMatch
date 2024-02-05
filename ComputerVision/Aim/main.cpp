#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "yolov5_dnn.h"

int main ()
{
    cv::Mat img;
    std::vector <DetectResult> results;
    cv::VideoCapture cap (1);
    std::string onnxpath = "../ne1000.onnx", path = "../0.jpg";
    YoloV5Detector detector (onnxpath);

    // img = cv::imread (path);
    // detector.detect (img, results);
    // detector.draw (img, results);

    // cv::imshow ("Img", img);
    // cv::waitKey (0);

    while (1)
    {
        // int i = 0;
        cap.read (img);
        // std::string save_path = "../imgs/" + std::to_string (i) + ".jpg";
        // cv::imwrite (save_path, img);
        // cv::Mat input = cv::imread (save_path);
        // i++;
        detector.detect (img, results);
        // detector.draw (img, results);
        detector.draw (img, results);
        cv::imshow ("Img", img);
        if (cv::waitKey (20) == 27)
        {
            break;
        }
        results.clear ();
        
    }
    

    return 0;
}
