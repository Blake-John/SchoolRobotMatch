#include "mathfunc.h"

void getStandard (std::vector <cv::Rect> &origin, std::vector <cv::Rect> &ordered)
{
    cv::Rect temp;
    //? by y
    for (int i = 0; i < origin.size () - 1; i++)
    {
        for (int j = 0; j < origin.size () - i - 1; j++)
        {
            if (origin[j].y > origin[j + 1].y)
            {
                temp = origin[j];
                origin[j] = origin[j + 1];
                origin[j + 1] = temp;
            }
        }
    }

    //? by x
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (origin[j].x > origin[j + 1].x)
            {
                temp = origin[j];
                origin[j] = origin[j + 1];
                origin[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        ordered.push_back (origin[i]);
    }
    
}

// void Aim (cv::Mat img, std::vector <cv::Rect> standard, int aimkey)
// {
//     cv::Mat show;
    
//     for (int i = 0; i < 5;)
//     {
//         img.copyTo (show);
//         std::vector <std::vector <cv::Scalar>> ColorRange;
//         getColorRange (show, ColorRange);
//         cv::Mat mask;
//         cv::inRange (img, ColorRange[0], ColorRange[1], mask);
//         //? find the color pieces from the mask
//         std::vector <std::vector <cv::Point>> contours;
//         cv::findContours (mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//         cv::drawContours (show, contours, -1, cv::Scalar (255, 255, 0), 2);
//         i = aimkey;
//     }

// }

void Aim (cv::Mat img, std::vector <cv::Rect> standard, int aimkey)
{
    cv::Mat imgHSV;
    double h, s, v;
    cv::cvtColor (img, imgHSV, cv::COLOR_BGR2HSV);
    cv::imshow ("HSV", imgHSV);
    // log (imgHSV.size ());
    // log (imgHSV.type ());
    cv::Rect bbox;
    
    //? get the H S V at one point
    s = imgHSV.at<cv::Vec2b> (standard[aimkey].y + (int)(standard[aimkey].height * 0.5), standard[aimkey].x + (int)(standard[aimkey].width * 0.5))[0]; //! s
    v = imgHSV.at<cv::Vec2b> (standard[aimkey].y + (int)(standard[aimkey].height * 0.5), standard[aimkey].x + (int)(standard[aimkey].width * 0.5))[1]; //! v
    h = imgHSV.at<cv::Vec2b> (standard[aimkey].y + (int)(standard[aimkey].height * 0.5), standard[aimkey].x + (int)(standard[aimkey].width * 0.5))[2]; //! h
    // log (h << " " << s << " " << v);
    std::cout << h << " " << s << " " << v << std::endl;
    
    int h_l, h_u, s_l, s_u, v_l, v_u;

    if (h + 20 < 179) h_u = h + 20;
    else h_u = 179;
    if (h - 20 > 0) h_l = h - 20;
    else h_l = 0;

    if (s + 44 < 255) s_u = s + 44;
    else s_u = 255;
    if (s - 44 > 0) s_l = s - 44;
    else s_l = 0;

    if (v + 39 <= 255) v_u = v + 39;
    else v_u = 255;
    if (v - 39 >= 0) v_l = v - 39;
    else v_l = 0;

    cv::Scalar lower (h_l, s_l, v_l);
    cv::Scalar upper (h_u, s_u, v_u);

    cv::Mat mask;
    cv::inRange (imgHSV, lower, upper, mask);
    //? find the color pieces from the mask
    std::vector <std::vector <cv::Point>> contours;
    cv::imshow ("Mask", mask);
    cv::findContours (mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours (img, contours, -1, cv::Scalar (255, 255, 0), 2);
    cv::imshow ("Aim", img);
}