/**
 * @file main.cpp
 * @author Blake John (2991151588@qq.com)
 * @brief the function to show the mid-term assessment
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 * @attention 此次考核使用图片进行展示，因为放假回老家搓了一个板，但忘记录个视频了，板带不走
 * 
 */

#include "mathfunc.h"

/// @brief 所有分类的名称
// std::vector <std::string> Classes = {"blake", "y_l", "y_d", "blue", "pink", "red", "orange", "green", "purple"};

// #define log(x) std::cout << x << std::endl;

int main ()
{
    // 初始化
    cv::Mat img;
    std::string modelpath = "../model/v3tiny-objs-1514.onnx";
    Yolo detector (modelpath);
    std::vector <Result> result;
    std::vector <std::vector <Result>> target;

    // 检测图像
    img = cv::imread ("../imgs/6.jpg");
    cv::Mat res;
    img.copyTo (res);
    detector.Detect (img, result);

    // 获取标准区色块
    order (result, target);

    std::vector <double> angles;

    // 记录上一次瞄准的点
    cv::Point history;
    history = C;

    for (int i = 0; i < 5; i++)
    {
        // 在画面中展示瞄准结果
        cv::Mat show;
        img.copyTo (show);
        cv::rectangle (show, target[i][0].bbox, cv::Scalar (255, 255, 0), 2);
        cv::rectangle (show, target[i][1].bbox, cv::Scalar (0, 255, 0), 2);
        // cv::rectangle (show, result[i].bbox, cv::Scalar (255, 255, 0), 2);
        cv::Point center (target[i][1].bbox.x + 0.5 * target[i][1].bbox.width, target[i][1].bbox.y + 0.5 * target[i][1].bbox.height);
        cv::circle (show, center, 10, cv::Scalar (0, 255, 255), -1);
        cv::putText (show, std::to_string (i), cv::Point (center.x - 5, center.y + 5), cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar (0, 0, 255), 1);

        // 计算偏角并在画面中展示
        angles = YawPitch (history, center);
        history = center;
        cv::putText (show, ("Yaw : " + std::to_string (angles[0])), cv::Point (50, 50), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar (255, 0, 255), 1);
        cv::putText (show, ("Pitch : " + std::to_string (angles[1])), cv::Point (50, 100), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar (255, 0, 255), 1);
        cv::imshow ("Aim", show);
        cv::waitKey (2000);
    }
}
