#include "mathfunc.h"
#include <iostream>
#include <cmath>


/// @brief get the d between two points
/// @param p1 
/// @param p2 
/// @return the d between two points
double ppD (cv::Point p1, cv::Point p2)
{
    return std::sqrt (std::pow (p1.x - p2.x, 2) + std::pow (p1.y - p2.y, 2));
}



/// @brief get the distance by the given parameters using the bounding rectangle of the target
/// @attention the method is used to calculated the distance normal to the camera CMOS
/// @param boundingrect the bounding rectangle of the target from `getTarget1`
/// @param true_x the true width of the target
/// @param true_y the true height of the target
/// @param pixel the pixel size of the camera
/// @param focus the focus of the camera
/// @return the mean distance derived from the distances in meter calculated by the width and height
double getDistance1 (cv::Rect boundingrect, double true_x, double true_y, double pixel, double focus)
{
    // DF100-720P has the pixel size of 3um * 3um and the focus of 2.8mm
    double px = (boundingrect.br ().x - boundingrect.tl ().x) * pixel * 0.000001;
    double py = (boundingrect.br ().y - boundingrect.tl ().y)* pixel * 0.000001;
    double D1, D2, D;
    // double D = 0.25;
    // double tx = px * D / focus;
    // double ty = py * D / focus;
    // std::cout << "px : " << px << '\t' << "tx : " << true_x << std::endl;
    // std::cout << "py : " << py << '\t' << "ty : " << true_y << std::endl;

    D1 = focus / px * true_x;
    D2 = focus / py * true_y;
    std::cout << D1 << " " << D2 << std::endl;
    D = D1 + D2 / 2;

    return D;
}



/// @brief get the distance by the given parameters using the Warped img of the target
/// @param imgWarp the warped img of the target from `warpTarget`, which means transform the target to be normal to the camera CMOS
/// @param true_x the true width of the target
/// @param true_y the true height of the target
/// @param pixel the pixel size of the camera
/// @param focus the focus of the camera
/// @return the mean distance derived from the distances in meter calculated by the width and height
double getDistance2 (cv::Mat imgWarp, double true_x, double true_y, double pixel, double focus)
{
    double px = (double)imgWarp.size ().width * pixel * 0.000001;
    double py = (double)imgWarp.size ().height * pixel * 0.000001;
    double D1, D2, D = 0;

    D1 = focus / px * true_x;
    D2 = focus / py * true_y;
    std::cout << D1 << " " << D2 << std::endl;
    D = D1 + D2 / 2;

    return D;
}



/// @brief order the point set with 4 points by the order of tl, tr, bl, br
/// @param originp the point set to be ordered
/// @return the ordered point set
std::vector <cv::Point> orderp (std::vector <cv::Point> originp)
{
    std::vector <int> sump, subp;
    std::vector <cv::Point> orderedp;

    for (int i = 0; i < originp.size (); i++)
    {
        sump.push_back (originp[i].x + originp[i].y);
        subp.push_back (originp[i].x - originp[i].y);
    }

    orderedp.push_back (originp[min_element (sump.begin (), sump.end ()) - sump.begin ()]);
    orderedp.push_back (originp[max_element (subp.begin (), subp.end ()) - subp.begin ()]);
    orderedp.push_back (originp[min_element (subp.begin (), subp.end ()) - subp.begin ()]);
    orderedp.push_back (originp[max_element (sump.begin (), sump.end ()) - sump.begin ()]);

    // std::cout << orderedp << std::endl;

    return orderedp;
}