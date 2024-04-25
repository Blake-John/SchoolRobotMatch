#include "process.h"



/**
 * @brief preprocess the img to get the edges
 * @attention it is not recommended to use the dilation
 * @param img_in the img to be preprocessed
 * @param to_dilate to_dilate choose whether to dilate the img or not. If to_dilate == 1, dilates the img, and it is by default 0
 * @param kernel_size the kernel size of the dilation, by default 0
 * @return returns the preprocessed img
 */
cv::Mat preprocess (cv::Mat img_in, bool to_dilate, int kernel_size)
{
    cv::Mat img_out;


    cv::cvtColor (img_in, img_out, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur (img_out, img_out, cv::Size (3, 3), 2, 2);
    cv::Canny (img_out, img_out, 75, 150);
    if (to_dilate)
    {
        cv::dilate (img_out, img_out, DilateKernel[kernel_size]);
    }
    cv::imshow ("ImgPre", img_out);
    
    return img_out;
}



/**
 * @brief get the vertexs of the target and draw it on the original img
 * @param img the original img
 * @param imgPre the preprocessed img from `preprocess` to find the target
 * @return the Point set of the vertexs of the target
 */
std::vector <cv::Point> getTarget (cv::Mat img, cv::Mat imgPre)
{
    std::vector <std::vector <cv::Point>> contours;
    cv::findContours (imgPre, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector <std::vector <cv::Point>> conpoly (contours.size ());
    

    for (int i = 0; i < contours.size (); i++)
    {
        cv::approxPolyDP (contours[i], conpoly[i], 20, true);
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
    cv::Mat img2;
    img.copyTo (img2);
    cv::drawContours (img2, conpoly, -1, cv::Scalar (0, 255, 0), 2);
    cv::imshow ("Img2", img2);

    return conpoly[0];
}



/**
 * @brief warp the target to be normal to the camera CMOS
 * @attention the tx should be the long side， and the ty should be the short side
 * @param img the original img
 * @param tp the vertexs of the target from `getTarget`, which can be unordered
 * @param tx the true width of the target (long side)
 * @param ty the true height of the target (short side)
 * @return the warped img of the target
 */
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