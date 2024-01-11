#include "process.h"

int main ()
{
    cv::Mat img, img_pre;
    int threshold = 10;
    std::string path = "../imgs/1-2.png";
    std::vector <cv::Mat> myStandards;
    std::vector <std::vector <cv::Scalar>> ColorRanges;

    img = cv::imread (path);

    img_pre = preprocess (img, img_pre);
    myStandards = getStandard (img_pre, img);
    ColorRanges = getColorRange (myStandards, threshold);
    cv::Rect boundingrect;

    for (int i = 0; i < ColorRanges.size (); i++)
    {
        boundingrect = Aim (img, ColorRanges[i]);
        cv::rectangle (img, boundingrect, cv::Scalar (0, 255, 255), 2);
        cv::circle (img, cv::Point (boundingrect.tl ().x + 15, boundingrect.tl ().y - 15), 25, cv::Scalar (0, 200, 255), cv::FILLED);
        cv::putText (img, std::to_string (i), boundingrect.tl (), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar (255, 255, 255), 3);
    }
    

    cv::imshow ("Img", img);
    cv::imshow ("ImgPre", img_pre);
    if (cv::waitKey (0) == 27)
    {
        std::exit (0);
    }
    

    return 0;
}