#include "funcs.h"

d_a D_A (cv::Mat img, double true_x, double true_y, cv::Point C, bool to_dilate, int kernel_size)
{
    d_a da;

    // preprocess the img
    cv::Mat imgPre, imgWarp;
    imgPre = preprocess (img, to_dilate, kernel_size);

    // get the vertexs of the target
    std::vector <cv::Point> points;
    points = getTarget (img, imgPre);

    // warp the target
    imgWarp = warpTarget (img, points, true_x, true_y);

    // get the distance
    double distance = getDistance (imgWarp, true_x, true_y, u, focus);
    da.distance = distance;

    // get the center of the target
    cv::Point center (getCenter (points));

    // draw the center on the img
    cv::circle (img, center, 5, cv::Scalar (255, 255, 0), -1);

    // calculate the deflection on the img
    double dx = center.x - C.x;
    double dy = C.y - center.y;

    // calculate the true deflection
    std::vector <double> true_deflection;
    true_deflection = TrueDeflection (imgWarp, dx, dy, true_x, true_y);

    // calculate the angle by two methods
    std::vector <double> angle1, angle2;
    angle1 = getAngle1 (distance, true_deflection[0], true_deflection[1]);
    angle2 = getAngle2 (dx, dy, u, focus);
    da.angle = {(angle1[0] + angle2[0]) / 2, (angle1[1] + angle2[1]) / 2};

    return da;
}