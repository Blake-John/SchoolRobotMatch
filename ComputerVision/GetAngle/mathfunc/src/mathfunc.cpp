#include "mathfunc.h"



/**
 * @brief get the d between two points (the pixel distance)
 * @param p1 
 * @param p2 
 * @return the d between two points
 */
double ppD (cv::Point p1, cv::Point p2)
{
    return std::sqrt (std::pow (p1.x - p2.x, 2) + std::pow (p1.y - p2.y, 2));
}




/**
 * @brief order the point set with 4 points by the order of tl, tr, bl, br
 * @param originp originp the point set to be ordered
 * @return the ordered point set
 */
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



/**
 * @brief Get the Center of the object
 * @param points the vertexs of the object
 * @return the center point of the object
 */
cv::Point getCenter (std::vector <cv::Point> points)
{
    cv::Moments mo = cv::moments (points);
    double x = mo.m10 / mo.m00, y = mo.m01 / mo.m00;
    return cv::Point ((int)x, (int)y);
}



/** 
 * @brief get the distance by the given parameters using the Warped img of the target
 * @param imgWarp the warped img of the target from `warpTarget`, which means transform the target to be normal to the camera CMOS
 * @param true_x the true width of the target
 * @param true_y the true height of the target
 * @param pixel the pixel size of the camera
 * @param focus the focus of the camera
 * @return the mean distance derived from the distances in meter calculated by the width and height
*/
double getDistance (cv::Mat imgWarp, double true_x, double true_y, double u, double focus)
{
    double px = (double)imgWarp.size ().width * u * 0.000001;
    double py = (double)imgWarp.size ().height * u * 0.000001;
    double D1, D2, D = 0;

    if (px > py)
    {
        D1 = focus / px * true_x;
        D2 = focus / py * true_y;
    }
    else
    {
        D1 = focus / py * true_x;
        D2 = focus / px * true_y;
    }
    

    std::cout << D1 << " " << D2 << std::endl;
    D = (D1 + D2) / 2;

    return D;
}


std::vector <double> TrueDeflection (cv::Mat imgWarp, double dx, double dy, double true_x, double true_y)
{
    std::vector <double> TD;
    double true_dx, true_dy;
    if (imgWarp.size ().width > imgWarp.size ().height)
    {
        true_dx = dx * true_x / imgWarp.size ().width;
        true_dy = dy * true_x/ imgWarp.size ().width;
    }
    else
    {
        true_dx = dx * true_y / imgWarp.size ().width;
        true_dy = dy * true_y / imgWarp.size ().width; 
    }
    

    TD.push_back (true_dx);
    TD.push_back (true_dy);

    return TD;
}


/**
 * @brief Get the horizontal and vertical Angle Deflection of the object
 * @param distance 
 * @param dx 
 * @param dy 
 * @return the angle set of the deflection
 */
std::vector <double> getAngle1 (double distance, double true_dx, double true_dy)
{
    std::vector <double> angle;
    double anglex, angley;
    anglex = std::atan (true_dx / distance) * 180 / PI;
    angley = std::atan (true_dy / distance) * 180 / PI;

    angle.push_back (anglex);
    angle.push_back (angley);

    return angle;
}

std::vector <double> getAngle2 (double dx, double dy, double u, double focus)
{
    std::vector <double> angle;
    double anglex, angley;
    anglex = std::atan (dx * u * 0.000001 / focus) * 180 / PI;
    angley = std::atan (dy * u * 0.000001 / focus) * 180 / PI;

    angle.push_back (anglex);
    angle.push_back (angley);

    return angle;
}