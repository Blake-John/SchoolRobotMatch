#include "yolo.h"
#include "mathfunc.h"

std::vector <std::string> Classes = {"blake", "y_l", "y_d", "blue", "pink", "red", "orange", "green", "purple"};


int main ()
{
    cv::Mat img;
    std::string modelpath = "../v3tiny-objs-1514.onnx";
    Yolo detector (modelpath);
    std::vector <Result> result;
    std::vector <std::vector <Result>> target;

    img = cv::imread ("../imgs/6.jpg");
    cv::Mat res;
    img.copyTo (res);
    detector.Detect (img, result);

    order (result, target);

    std::vector <double> angles;
    cv::Point history;
    history = C;

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
        angles = YawPitch (history, center);
        history = center;
        cv::putText (show, ("Yaw : " + std::to_string (angles[0])), cv::Point (50, 50), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar (255, 0, 255), 1);
        cv::putText (show, ("Pitch : " + std::to_string (angles[1])), cv::Point (50, 100), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar (255, 0, 255), 1);
        cv::imshow ("Aim", show);
        cv::waitKey (2000);
    }
}