#include "process.h"


/// @brief To preprocess the img by converting to Gray, detecting the edges, dilating the edges
/// @param img_in 
/// @param img_out 
/// @return the preprocessed img
cv::Mat preprocess (cv::Mat img_in, cv::Mat img_out)
{
    
    
    cv::cvtColor (img_in, img_out, cv::COLOR_BGR2GRAY);
    // cv::GaussianBlur (img_out, img_out, cv::Size (3, 3), 1, 1);
    cv::Canny (img_out, img_out, 50, 100);

    cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (1, 1));
    cv::dilate (img_out, img_out, kernel);

    return img_out;
}



/// @brief get the standard pieces of the img by finding the color contours and choose the right contours by area, coordinate
/// @param img_pre the img preprocessed by `proprocess`
/// @param img the img to crop the standard pieces from
/// @return the vector of the standard imgs
std::vector <cv::Mat> getStandard (cv::Mat img_pre, cv::Mat img)
{
    std::vector <cv::Mat> myStandards;
    std::vector <cv::Rect> mySet_origin;

    //? find the contours and its bounding rectangles
    std::vector <std::vector <cv::Point>> contours;
    cv::findContours (img_pre, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size (); i++)
    {
        double area = cv::contourArea (contours[i]);
        cv::Rect boundingrect;
        if (area > 10000 and area < 30000)
        {
            // log (area);
            boundingrect = cv::boundingRect (contours[i]);
            // cv::drawContours (img, contours, i, cv::Scalar (0, 255, 0), 2);
            // cv::rectangle (img, boundingrect, cv::Scalar (0, 255, 0), 2);
            mySet_origin.push_back (boundingrect);
        }
    }

    //? reorder the bounding rectangles by y
    cv::Rect temp;
    for (int i = 0; i < mySet_origin.size () - 1; i++)
    {
        for (int j = 0; j < mySet_origin.size () - i - 1; j++)
        {
            if (mySet_origin[j].y > mySet_origin[j + 1].y)
            {
                temp = mySet_origin[j];
                mySet_origin[j] = mySet_origin[j + 1];
                mySet_origin[j + 1] = temp;
            }
        }
        
    }

    std::vector <cv::Rect> mySet_s_no;
    for (int i = 0; i < 5; i++)
    {
        mySet_s_no.push_back (mySet_origin[i]);
    }

    //? reorder the bounding rectangles by x
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (mySet_s_no[j].x > mySet_s_no[j + 1].x)
            {
                temp = mySet_s_no[j];
                mySet_s_no[j] = mySet_s_no[j + 1];
                mySet_s_no[j + 1] = temp;
            }
            
        }
    }
    
    //? crop the img to get the standard img
    cv::Mat imgCrop;
    for (int i = 0; i < 5; i++)
    {
        imgCrop = img (cv::Rect (mySet_s_no[i].x + 20, mySet_s_no[i].y + 20, (mySet_s_no[i].br ().x - mySet_s_no[i].tl ().x) / 2, (mySet_s_no[i].br ().x -mySet_s_no[i].tl ().x) / 2));
        cv::resize (imgCrop, imgCrop, cv::Size (), 3, 3);
        myStandards.push_back (imgCrop);
    }
    
    
    //? show the standard imgs
    cv::imshow ("S0", myStandards[0]);
    cv::imshow ("S1", myStandards[1]);
    cv::imshow ("S2", myStandards[2]);
    cv::imshow ("S3", myStandards[3]);
    cv::imshow ("S4", myStandards[4]);
    
    
    return myStandards;
}


/// @brief get the color value from the standard imgs and calculate the range using the threshold
/// @param myStandard the right ordered standard imgs to be referred to get the color range. got by `getStandard`
/// @param threshold the threshold of the color range
/// @return return the vector of the color range, in which are the vector of lower and upper value
std::vector <std::vector <cv::Scalar>> getColorRange (std::vector <cv::Mat> myStandard, int threshold)
{
    cv::Mat img, imgHSV;
    std::vector <std::vector <cv::Scalar>> ColorRange;

    for (int i = 0; i < myStandard.size (); i++)
    {
        double h, s, v;
        myStandard[i].copyTo (img);
        cv::cvtColor (img, imgHSV, cv::COLOR_BGR2HSV);
        // log (imgHSV.size ());
        // log (imgHSV.type ());
        
        //? get the H S V at one point
        s = imgHSV.at<cv::Vec2b> (50, 50)[0]; //! s
        v = imgHSV.at<cv::Vec2b> (50, 50)[1]; //! v
        h = imgHSV.at<cv::Vec2b> (50, 50)[2]; //! h
        // log (h << " " << s << " " << v);
        
        int h_l, h_u, s_l, s_u, v_l, v_u;

        if (h + threshold < 179) h_u = h + threshold;
        else h_u = 179;
        if (h - threshold > 0) h_l = h - threshold;
        else h_l = 0;

        if (s + threshold < 255) s_u = s + threshold;
        else s_u = 255;
        if (s - threshold > 0) s_l = s - threshold;
        else s_l = 0;

        if (v + threshold <= 255) v_u = v + threshold;
        else v_u = 255;
        if (v - threshold >= 0) v_l = v - threshold;
        else v_l = 0;

        cv::Scalar lower (h_l, s_l, v_l);
        cv::Scalar upper (h_u, s_u, v_u);
        ColorRange.push_back ({lower, upper});
        
    }

    // for (int i = 0; i < ColorRange.size (); i++)
    // {
    //     std::cout << ColorRange[i][0] << " " << ColorRange[i][1] << std::endl;;
    // }
    
    return ColorRange;
}


/// @brief Aim the target color pieces by the color ranges passed to it
/// @param img the input img which is aimmed
/// @param colorrange the color ranges got by `getColorRange` , which meet the order of the standard
/// @return returns the bounding rectangles of the aimmed color pieces which contain the position information
cv::Rect Aim (cv::Mat img, std::vector <cv::Scalar> colorrange)
{
    //? get the mask
    cv::Mat imgHSV, imgMask;
    cv::cvtColor (img, imgHSV, cv::COLOR_BGR2HSV);
    cv::inRange (imgHSV, colorrange[0], colorrange[1], imgMask);

    //? find the color pieces from the mask
    std::vector <std::vector <cv::Point>> contours;
    cv::findContours (imgMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // cv::imshow ("Mask", imgMask);

    std::vector <cv::Point> temp;
    cv::Rect boundingrect;
    for (int i = 0; i < contours.size () - 1; i++)
    {
        double area1, area2;
        for (int j = 0; j < contours.size () - 1 - i; j++)
        {
            area1 = cv::contourArea (contours[j]);
            area2 = cv::contourArea (contours[j + 1]);
            if (area1 < area2)
            {
                temp = contours[j];
                contours[j] = contours[j + 1];
                contours[j + 1] = temp;
            }   
        }   
    }
    boundingrect = cv::boundingRect (contours[0]);

    return boundingrect;
}