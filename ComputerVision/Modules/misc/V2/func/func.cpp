#include "func.h"
#define PI (double)3.1415926

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

std::vector <double> getAngle (double dx, double dy, double u, double d)
{
    std::vector <double> angle;
    double anglex, angley;
    anglex = std::atan (dx * u * 0.000001 / d) * 180 / PI;
    angley = std::atan (dy * u * 0.000001 / d) * 180 / PI;

    angle.push_back (anglex);
    angle.push_back (angley);

    return angle;
}