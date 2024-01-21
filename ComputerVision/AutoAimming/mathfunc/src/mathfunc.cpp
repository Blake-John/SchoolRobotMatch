#include "mathfunc.h"

/// @brief calculate the center of the bounding rectangle
/// @param boundingrect the bounding rectangle to be calculated
/// @return the point of the center with the type of `cv::Point`
cv::Point getCenter (cv::Rect boundingrect)
{
    int x = (boundingrect.br ().x + boundingrect.tl ().x) / 2;
    int y = (boundingrect.br ().y + boundingrect.tl ().y) / 2;
    
    return cv::Point (x, y);
}