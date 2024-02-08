#include "yolov3.h"
#include "func.h"

std::vector <std::string> Classes = {"blake", "y_l", "y_d", "blue", "pink", "red", "orange", "green", "purple"};

int main ()
{
    cv::Mat img;
    std::string modelpath = "../yolov3-objs-1000.onnx";
    Yolo yolodetector (modelpath);
    Result result;

    img = cv::imread ("../0.jpg");
    yolodetector.Detect (img, result);
    for (int i = 0; i < result.bboxes.size (); i++)
    {
        cv::rectangle (img, result.bboxes[i], cv::Scalar (255, 255, 0), 2);
        cv::rectangle (img, cv::Point (result.bboxes[i].x, result.bboxes[i].y - 25), cv::Point (result.bboxes[i].br ().x, result.bboxes[i].y), cv::Scalar (255, 255, 0), -1);
        cv::putText (img, Classes[result.classids[i]], cv::Point (result.bboxes[i].tl ().x, result.bboxes[i].tl ().y - 5), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar (255, 255, 255), 2);
    }
    
    cv::imshow ("Img", img);
    cv::waitKey (0);
    

    return 0;
}