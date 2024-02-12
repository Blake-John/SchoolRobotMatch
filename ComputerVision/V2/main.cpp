#include "yolov3.h"
#include "func.h"

std::vector <std::string> Classes = {"blake", "y_l", "y_d", "blue", "pink", "red", "orange", "green", "purple"};

// int main ()
// {
//     cv::Mat img;
//     std::string modelpath = "../v3tiny-objs-1514.onnx";
//     Yolo yolodetector (modelpath);
//     std::vector <Result> result;
//     std::vector <std::vector <Result>> target;

//     img = cv::imread ("../53.jpg");
//     cv::Mat res;
//     img.copyTo (res);
//     yolodetector.Detect (img, result);
//     for (int i = 0; i < result.size (); i++)
//     {
//         cv::rectangle (res, result[i].bbox, cv::Scalar (255, 255, 0), 2);
//         cv::rectangle (res, cv::Point (result[i].bbox.x, result[i].bbox.y - 25), cv::Point (result[i].bbox.br ().x, result[i].bbox.y), cv::Scalar (255, 255, 0), -1);
//         cv::putText (res, Classes[result[i].classid], cv::Point (result[i].bbox.tl ().x, result[i].bbox.tl ().y - 5), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar (255, 255, 255), 2);
//     }
//     cv::imshow ("Result", res);
//     order (result, target);
//     for (int i = 0; i < 5; i++)
//     {
//         cv::Mat show;
//         img.copyTo (show);
//         cv::rectangle (show, target[i][0].bbox, cv::Scalar (255, 255, 0), 2);
//         cv::rectangle (show, target[i][1].bbox, cv::Scalar (0, 255, 0), 2);
//         // cv::rectangle (show, result[i].bbox, cv::Scalar (255, 255, 0), 2);
//         cv::imshow ("Aim", show);
//         cv::waitKey (2000);
//     }
    
//     // cv::imshow ("Img", img);
//     // cv::waitKey (0);
    

//     return 0;
// }

int main ()
{
    cv::Mat img, res;
    cv::VideoCapture cap (1);
    cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);
    cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);
    std::string modelpath = "../v5n-objs-2000-105.onnx";
    Yolo yolodetector (modelpath);
    std::vector <Result> result;
    std::vector <std::vector <Result>> target;

    while (1)
    {
        cap.read (img);
        img.copyTo (res);
        yolodetector.Detect (img, result);
        for (int i = 0; i < result.size (); i++)
        {
            cv::rectangle (res, result[i].bbox, cv::Scalar (255, 255, 0), 2);
            cv::rectangle (res, cv::Point (result[i].bbox.x, result[i].bbox.y - 25), cv::Point (result[i].bbox.br ().x, result[i].bbox.y), cv::Scalar (255, 255, 0), -1);
            cv::putText (res, Classes[result[i].classid], cv::Point (result[i].bbox.tl ().x, result[i].bbox.tl ().y - 5), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar (255, 255, 255), 2);
        }
        result.clear ();
        cv::imshow ("Detect", res);

        if (cv::waitKey (20) == 27)
        {
            break;
        }
        
    }
    
}