#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "process.h"
#include "mathfunc.h"

int main ()
{
    cv::Mat img, imgPre, imgWarp;
    cv::Rect boundingrect;
    std::vector <cv::Point> tp;
    double tx = 0.14;
    double ty = 0.065;
    double u = 3;
    double focus = 0.0028;
    double D; // for the introduction : 0.18, for the linear algerbra : 0.25
    img = cv::imread ("../4.jpg");
    
    imgPre = preprocess (img);
    boundingrect = getTarget1 (img, imgPre);
    tp = getTarget2 (img, imgPre);
    imgWarp = warpTarget (img, tp, tx, ty);

    D = getDistance1 (boundingrect, tx, ty, u, focus);
    D = getDistance2 (imgWarp, tx, ty, u, focus);

    cv::imshow ("Img", img);
    cv::imshow ("ImgOut", imgPre);
    cv::imshow ("ImgWarp", imgWarp);

    if (cv::waitKey (0) == 27)
    {
        std::exit (0);
    }
    

    return 0;
}