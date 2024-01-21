#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

/// @brief shoot the img and save it in the specific path
/// @return 
int main ()
{
    cv::VideoCapture cap (2);
    cv::Mat img;
    cap.set (cv::CAP_PROP_FRAME_WIDTH, 1080);
    cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);

    while (1)
    {
        cap.read (img);
        cv::imshow ("Cam", img);
        if (cv::waitKey (20) == 27)
        {
            break;
        }
        
        
    }
    
    cv::imwrite ("../../4.jpg", img);

    return 0;
}