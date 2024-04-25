#include "yolov3.h"
#include "func.h"
#define u (double)3
#define d (double)0.0031945

std::vector <std::string> Classes = {"blake", "y_l", "y_d", "blue", "pink", "red", "orange", "green", "purple"};

int main ()
{
    cv::Mat img;
    std::string modelpath = "../v3tiny-3000.onnx";
    Yolo yolodetector (modelpath);
    std::vector <Result> result;
    std::vector <std::vector <Result>> target;

    img = cv::imread ("../testimg.jpg");
    cv::Mat res;
    img.copyTo (res);
    yolodetector.Detect (img, result);
    for (int i = 0; i < result.size (); i++)
    {
        cv::rectangle (res, result[i].bbox, cv::Scalar (255, 255, 0), 2);
        cv::rectangle (res, cv::Point (result[i].bbox.x, result[i].bbox.y - 25), cv::Point (result[i].bbox.br ().x, result[i].bbox.y), cv::Scalar (255, 255, 0), -1);
        cv::putText (res, Classes[result[i].classid], cv::Point (result[i].bbox.tl ().x, result[i].bbox.tl ().y - 5), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar (255, 255, 255), 2);
    }
    cv::imshow ("Result", res);
    order (result, target);
    std::vector <double> angles, history;
    history.push_back (0.5 * 1280);
    history.push_back (0.5 * 720);
    for (int i = 0; i < 5; i++)
    {
        cv::Mat show;
        img.copyTo (show);
        cv::rectangle (show, target[i][0].bbox, cv::Scalar (255, 255, 0), 2);
        cv::rectangle (show, target[i][1].bbox, cv::Scalar (0, 255, 0), 2);
        // cv::rectangle (show, result[i].bbox, cv::Scalar (255, 255, 0), 2);
        cv::Point center (target[i][1].bbox.x + 0.5 * target[i][1].bbox.width, target[i][1].bbox.y + 0.5 * target[i][1].bbox.height);
        cv::circle (show, center, 10, cv::Scalar (0, 255, 255), -1);
        cv::putText (show, std::to_string (i), cv::Point (center.x - 5, center.y + 5), cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar (0, 0, 255), 1);
        double dx = center.x - history[0];
        double dy = history[1] - center.y;
        angles = getAngle (dx, dy, u, d);
        history.clear ();
        history.push_back (center.x);
        history.push_back (center.y);
        cv::putText (show, ("X : " + std::to_string (angles[0])), cv::Point (50, 50), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar (255, 0, 255), 1);
        cv::putText (show, ("Y : " + std::to_string (angles[1])), cv::Point (50, 100), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar (255, 0, 255), 1);
        cv::imshow ("Aim", show);
        cv::waitKey (2000);
    }
 
    // cv::imshow ("Img", img);
    // cv::waitKey (0);
 

    return 0;
}

// int main ()
// {
//     cv::Mat img, res;
//     cv::VideoCapture cap (0);
//     cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);
//     cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);
//     std::string modelpath = "../v5n-objs-2000-105.onnx";
//     Yolo yolodetector (modelpath);
//     std::vector <Result> result;
//     std::vector <std::vector <Result>> target;
// 
//     while (1)
//     {
//         cap.read (img);
//         img.copyTo (res);
//         yolodetector.Detect (img, result);
//         for (int i = 0; i < result.size (); i++)
//         {
//             cv::rectangle (res, result[i].bbox, cv::Scalar (255, 255, 0), 2);
//             cv::rectangle (res, cv::Point (result[i].bbox.x, result[i].bbox.y - 25), cv::Point (result[i].bbox.br ().x, result[i].bbox.y), cv::Scalar (255, 255, 0), -1);
//             cv::putText (res, Classes[result[i].classid], cv::Point (result[i].bbox.tl ().x, result[i].bbox.tl ().y - 5), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar (255, 255, 255), 2);
//         }
//         result.clear ();
//         cv::imshow ("Detect", res);
// 
//         if (cv::waitKey (20) == 27)
//         {
//             break;
//         }
//         
//     }
//     
// }
