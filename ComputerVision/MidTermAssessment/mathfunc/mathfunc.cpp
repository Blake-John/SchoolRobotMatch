#include "mathfunc.h"
#include <cmath>

std::vector <double> YawPitch (cv::Point pt1, cv::Point pt2)
{
    std::vector <double> Angles;
    double yaw, pitch;

    double dx = (pt2.x - pt1.x) * u * 0.000001;
    double dy = (pt2.y - pt1.y) * u * 0.000001;
    double dx1 = (pt1.x - C.x) * u * 0.000001;
    double dx2 = (pt2.x - C.x) * u * 0.000001;
    double dy1 = (pt1.y - C.y) * u * 0.000001;
    double dy2 = (pt2.y - C.y) * u * 0.000001;

    double l_11 = std::sqrt (std::pow (dx1, 2) + std::pow (d, 2));
    double l_12 = std::sqrt (std::pow (dx2, 2) + std::pow (d, 2));
    if (dx >= 0) yaw = std::acos ((std::pow (l_11, 2) + std::pow (l_12, 2) - std::pow (dx, 2)) / (2 * l_11 * l_12)) * 180 / PI;
    else yaw = -std::acos ((std::pow (l_11, 2) + std::pow (l_12, 2) - std::pow (dx, 2)) / (2 * l_11 * l_12)) * 180 / PI;

    double l_21 = std::sqrt (std::pow (dy1, 2) + std::pow (d, 2));
    double l_22 = std::sqrt (std::pow (dy2, 2) + std::pow (d, 2));
    if (dy >= 0) pitch = std::acos ((std::pow (l_21, 2) + std::pow (l_22, 2) - std::pow (dy, 2)) / (2 * l_21 * l_22)) * 180 / PI;
    else pitch = -std::acos ((std::pow (l_21, 2) + std::pow (l_22, 2) - std::pow (dy, 2)) / (2 * l_21 * l_22)) * 180 / PI;
    
    Angles.push_back (yaw);
    Angles.push_back (pitch);

    return Angles;
}


void order (std::vector <Result> &result, std::vector <std::vector <Result>> &target)
{
    for (int i = 0; i < result.size () - 1; i++)
    {
        for (int j = 0; j < result.size () - i - 1; j++)
        {
            if (result[j].bbox.y > result[j + 1].bbox.y)
            {
                Result temp;
                temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
                        
        }
        
    }
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (result[j].bbox.x > result[j + 1].bbox.x)
            {
                Result temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
            
        }
        
    }
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 5; j < result.size (); j++)
        {
            if (result[i].classid == result[j].classid)
            {
                target.push_back ({result[i], result[j]});
            }
        }
    }
    
}