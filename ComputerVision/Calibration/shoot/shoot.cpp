#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
// #include <fstream>

#define log(x) std::cout << x << std::endl;

int main ()
{
    cv::VideoCapture cap (1);
    cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);

    cv::Mat img;
    int key;
    double d;

    // std::fstream f;
    // f.open ("../../imgs/distances.csv");
    while (1)
    {
        std::string path = "../../imgs/";

        cap.read (img);
        cv::imshow ("Cam", img);

        key = cv::waitKey (20);
        if (key == 48)
        {
            log ("Please input the distance : ");std::cin >> d;
            path += std::to_string ((int)d);
            path += ".jpg";
            cv::imwrite (path, img);
            // f << path << std::endl;

        }
        if (key == 27)
        {
            break;
        }
    }
    // f.close ();
    // log ("File is saved !");
    
    return 0;
}