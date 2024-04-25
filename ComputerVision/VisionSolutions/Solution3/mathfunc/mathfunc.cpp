#include "mathfunc.h"
#include <cmath>


/**
 * @brief 通过输入的两个点获取激光模块偏转所需的欧拉角分量，通过余弦定理计算
 * @note 计算使用了最简单的相似以及三角形之间的边角关系来得到 `yaw` 和 `pitch`，
 * 由于结构的限制以及激光模块本身的特殊性，只有2个转轴并且其中一个转轴是固定的，才能用这种简单的方法计算
 * 
 * @param pt1 起点
 * @param pt2 终点
 * @return std::vector <double> 欧拉角分量的数组，{Yaw, Pitch}
 */
std::vector <double> YawPitch (cv::Point pt1, cv::Point pt2, cv::Point Center)
{
    std::vector <double> Angles;
    double yaw, pitch;

    double dx = (pt2.x - pt1.x) * u * 0.000001;
    double dy = (pt2.y - pt1.y) * u * 0.000001;
    double dx1 = (pt1.x - Center.x) * u * 0.000001;
    double dx2 = (pt2.x - Center.x) * u * 0.000001;
    double dy1 = (pt1.y - Center.y) * u * 0.000001;
    double dy2 = (pt2.y - Center.y) * u * 0.000001;

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

