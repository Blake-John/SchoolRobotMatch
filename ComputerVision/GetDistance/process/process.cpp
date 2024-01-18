#include "process.h"
#include "mathfunc.h"
#include <iostream>

#define log(x) std::cout << x << std::endl;



/// @brief preprocess the img at the following steps : convert to the Gray Scale, apply GaussianBlur, detect the edges (or may be you can dilate it to get the greater result)
/// @param img_in 
/// @return the preprocessed img
cv::Mat preprocess (cv::Mat img_in)
{
    cv::Mat img_out;

    // cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (2, 2), cv::Point (1, 1));

    cv::cvtColor (img_in, img_out, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur (img_out, img_out, cv::Size (3, 3), 2);
    cv::Canny (img_out, img_out, 75, 150);
    // cv::dilate (img_out, img_out, kernel);

    return img_out;
}



/// @brief get the target and draw it on the original img
/// @param img the img to draw the target
/// @param imgPre the preprocessed img from `preprocess` to find the target
/// @return the bounding rectangle of the target
cv::Rect getTarget1 (cv::Mat img, cv::Mat imgPre)
{
    std::vector <std::vector <cv::Point>> contours;
    std::vector <cv::Rect> rects;
    cv::findContours (imgPre, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // std::vector <std::vector <cv::Point>> conpoly (contours.size ());

    for (int i = 0; i < contours.size (); i++)
    {
        double area = cv::contourArea (contours[i]);
        cv::Rect boundingrect;
        if (area > 2000)
        {
            // cv::approxPolyDP (contours[i], conpoly[i], 5, true);
            cv::drawContours (img, contours, i, cv::Scalar (0, 255, 0), 2);
            // cv::drawContours (img, conpoly, i, cv::Scalar (0, 255, 0), 2);
            boundingrect = cv::boundingRect (contours[i]);
            rects.push_back (boundingrect);
        }
    }

    for (int i = 0; i < rects.size () - 1; i++)
    {
        for (int j = 0; j < rects.size () - i - 1; j++)
        {
            if (rects[j].area () < rects[j + 1].area ())
            {
                cv::Rect temp = rects[j];
                rects[j] = rects[j + 1];
                rects[j + 1] = temp;
            }
            
        }
        
    }

    cv::rectangle (img, rects[0], cv::Scalar (255, 255, 100), 2);

    return rects[0];

}



/// @brief get the vertexs of the target and draw it on the original img
/// @param img the original img
/// @param imgPre the preprocessed img from `preprocess` to find the target
/// @return the Point set of the vertexs of the target
std::vector <cv::Point> getTarget2 (cv::Mat img, cv::Mat imgPre)
{
    std::vector <std::vector <cv::Point>> contours;
    cv::findContours (imgPre, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector <std::vector <cv::Point>> conpoly (contours.size ());
    

    for (int i = 0; i < contours.size (); i++)
    {
        cv::approxPolyDP (contours[i], conpoly[i], 5, true);
        double area = cv::contourArea (contours[i]);
        if (area > 2000)
        {
            cv::drawContours (img, conpoly, i, cv::Scalar (0, 255, 0), 2);
        }       
    }

    for (int i = 0; i < conpoly.size () - 1; i++)
    {
        for (int j = 0; j < conpoly.size () - 1 - i; j++)
        {
            double area1 = cv::contourArea (conpoly[j]);
            double area2 = cv::contourArea (conpoly[j + 1]);
            if (area1 < area2)
            {
                std::vector <cv::Point> temp = conpoly[j];
                conpoly[j] = conpoly[j + 1];
                conpoly[j + 1] = temp;
            }
        }
    }

    return conpoly[0];
}



/// @brief warp the target to be normal to the camera CMOS
/// @attention the method to warp the img has been abandoned, because the method to warp the target requires the target has a horizontal or vertical side, but another method can warp any target
/// @param img the original img
/// @param tp the point set of the vertexs of the target from `getTarget2`
/// @param tx the true width of the target (long side)
/// @param ty the true height of the target (short side)
/// @return tht warped img of the target
cv::Mat warpTarget1 (cv::Mat img, std::vector <cv::Point> tp, double tx, double ty)
{
    cv::Mat imgWarp;
    double ratio = (double)ty / (double)tx;
    std::vector <cv::Point> points = orderp (tp);

    int px = std::max (points[1].x - points[0].x, points[3].x - points[2].x);
    int py = std::max (points[2].y - points[0].y, points[3].y - points[1].y);
    int standard, another;
    cv::Point2f src[4] = {(cv::Point2f)points[0], (cv::Point2f)points[1], (cv::Point2f)points[2],(cv::Point2f)points[3]};
    cv::Point2f dst[4];
    if (px >= py)
    {
        standard = px;
        another = standard * ratio;
        dst[0] = cv::Point2f (0, 0);
        dst[1] = cv::Point2f (standard, 0);
        dst[2] = cv::Point2f (0, another);
        dst[3] = cv::Point2f (standard, another);

        cv::Mat matrix = cv::getPerspectiveTransform (src, dst);
        cv::warpPerspective (img, imgWarp, matrix, cv::Size (standard, another));

    }
    else
    {
        standard = py;
        another = standard * ratio;
        dst[0] = cv::Point2f (0, 0);
        dst[1] = cv::Point2f (another, 0);
        dst[2] = cv::Point2f (0, standard);
        dst[3] = cv::Point2f (another, standard);

        cv::Mat matrix = cv::getPerspectiveTransform (src, dst);
        cv::warpPerspective (img, imgWarp, matrix, cv::Size (another, standard));
    }

    return imgWarp;

}



/// @brief warp the target
/// @param img the original img
/// @param tp the vertexs of the target from `getTarget2`, which can be unordered
/// @param tx the true width of the target (long side)
/// @param ty the true height of the target (short side)
/// @return the warped img of the target
cv::Mat warpTarget (cv::Mat img, std::vector <cv::Point> tp, double tx, double ty)
{
    cv::Mat imgWarp;
    double ratio = (double)ty / (double)tx;
    std::vector <cv::Point> points = orderp (tp);

    int pw = std::max (ppD (points[0], points[1]), ppD (points[2], points[3]));
    int ph = std::max (ppD (points[0], points[2]), ppD (points[1], points[3]));
    int l, s;
    cv::Point2f src[4] = {(cv::Point2f)points[0], (cv::Point2f)points[1], (cv::Point2f)points[2],(cv::Point2f)points[3]};
    cv::Point2f dst[4];
    if (pw >= ph)
    {
        l = pw;
        s = l * ratio;
        dst[0] = cv::Point2f (0, 0);
        dst[1] = cv::Point2f (l, 0);
        dst[2] = cv::Point2f (0, s);
        dst[3] = cv::Point2f (l, s);

        cv::Mat matrix = cv::getPerspectiveTransform (src, dst);
        cv::warpPerspective (img, imgWarp, matrix, cv::Size (l, s));

    }
    else
    {
        l = ph;
        s = l * ratio;
        dst[0] = cv::Point2f (0, 0);
        dst[1] = cv::Point2f (s, 0);
        dst[2] = cv::Point2f (0, l);
        dst[3] = cv::Point2f (s, l);

        cv::Mat matrix = cv::getPerspectiveTransform (src, dst);
        cv::warpPerspective (img, imgWarp, matrix, cv::Size (s, l));
    }

    return imgWarp;
}