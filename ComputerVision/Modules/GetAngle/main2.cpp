#include "funcs.h"

const cv::Point C (640, 360);

int main ()
{
    log ("Configuration Succeed !");
    cv::Mat img;
    cv::VideoCapture cap (1);
    cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);
    d_a da;
    double true_x, true_y;
    int key = 0;

    log ("Please input the true width (long side): "); std::cin >> true_x;
    log ("Please input the true height (short side) : "); std::cin >> true_y;



    while (1)
    {
        cap.read (img);
        
        
        if (cv::waitKey (10) == 48)
        {
            da = D_A (img, true_x, true_y, C, 1, 2);

            log ("The Distance from the target : " << da.distance);
            log ("The Deflection Angle of X Asix : " << da.angle[0]);
            log ("The Deflection Angle of Y Asix : " << da.angle[1]);           
        }

        cv::imshow ("Img", img);

        if (cv::waitKey (10) == 27)
        {
            break;
        }
    }

    return (0);
}