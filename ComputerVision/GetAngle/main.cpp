#include "mathfunc.h"
#include "process.h"

#define u (double)3
#define focus (double)0.0028
#define d 0.0031945

const cv::Point C (640, 360);

int main ()
{
    log ("Configuration Succeed !");
    cv::Mat img, imgPre, imgWarp;
    std::vector <cv::Point> tp;
    double D;
    std::vector <double> angle1, angle2;
    std::vector <double> true_deflection;
    cv::Point center;
    double dx, dy, true_dx, true_dy;


    double tx, ty;
    log ("Please input the true x : "); std::cin >> tx;
    log ("Please input the true y : "); std::cin >> ty;

    img = cv::imread ("../4.jpg");
    imgPre = preprocess (img);
    tp = getTarget (img, imgPre);
    imgWarp = warpTarget (img, tp, tx, ty);
    D = getDistance (imgWarp, tx, ty, u, focus);
    center = getCenter (tp);
    log ("The Center of the Target : " << center);
    cv::circle (img, tp[0], 5, cv::Scalar (0, 0, 255), cv::FILLED);
    cv::circle (img, center, 5, cv::Scalar (255, 255, 0), -1);
    dx = center.x - C.x;
    dy = C.y - center.y;

    true_deflection = TrueDeflection (imgWarp, dx, dy, tx, ty);

    angle1 = getAngle1 (D, true_deflection[0], true_deflection[1]);
    angle2 = getAngle2 (dx, dy, u, focus);

    log ("The Distance from the target : " << D);
    log ("The Deflection Angle of X Asix : " << angle1[0] << '\t' << angle2[0]);
    log ("The Deflection Angle of Y Asix : " << angle1[1] << '\t' << angle2[1]);

    cv::imshow ("Img", img);
    cv::imshow ("ImgPre", imgPre);
    cv::imshow ("ImgWarp", imgWarp);

    if (cv::waitKey (0) == 27)
    {
        std::exit (0);
    }
    

    return 0;
}