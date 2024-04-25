#include "process.h"
#include "mathfunc.h"
#include <opencv2/highgui.hpp>
#include <vector>

std::vector <std::vector <int>> colorange = {{179, 56, 104, 0, 15, 50}, {109, 59, 173, 66, 0, 141}, {18, 219, 189, 0, 165, 151}, {179, 191, 193, 133, 77, 153},\
	{82, 172, 134, 41, 80, 96}, {179, 209, 185, 148, 125, 86}, {26, 191, 181, 17, 140, 154}, {129, 211, 131, 94, 58, 51}, {39, 176, 198, 27, 138, 146}, {29, 89, 80, 19, 50, 54}};


// int main ()
// {
//     cv::Mat img, img_pre;
//     int threshold = 10;
//     std::string path = "../imgs/2.jpg";
//     std::vector <cv::Mat> myStandards;
//     std::vector <std::vector <cv::Scalar>> ColorRanges;
// 
//     img = cv::imread (path);
//     // std::cout << img << std::endl;
// 
//     img_pre = preprocess (img, img_pre);
//     // myStandards = getStandard (img_pre, img);
//     // ColorRanges = getColorRange (myStandards, threshold);
//     // cv::Rect boundingrect;
// 
//     // for (int i = 0; i < ColorRanges.size (); i++)
//     // {
//     //     boundingrect = Aim (img, ColorRanges[i]);
//     //     cv::rectangle (img, boundingrect, cv::Scalar (0, 255, 255), 2);
//     //     cv::circle (img, cv::Point (boundingrect.tl ().x + 15, boundingrect.tl ().y - 15), 25, cv::Scalar (0, 200, 255), cv::FILLED);
//     //     cv::putText (img, std::to_string (i), boundingrect.tl (), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar (255, 255, 255), 3);
//     //     cv::Point p = getCenter (boundingrect);
//     //     log (p);
//     // }
//     
// 
//     cv::imshow ("Img", img);
//     cv::imshow ("ImgPre", img_pre);
//     while (cv::waitKey (20) != 27);
// 
//     return 0;
// }

int main ()
{
	std::vector <std::vector <cv::Rect>> result;
    cv::Mat img, img_pre;
    int threshold = 10;
    std::vector <cv::Mat> myStandards;
    std::vector <std::vector <cv::Scalar>> ColorRanges;

    cv::VideoCapture cap ("../imgs/target.mp4");
    while (1)
    {
        cap.read (img);
        img_pre = preprocess (img);
		cv::imshow ("ImgPre", img_pre);
		

        // myStandards = getStandard (img_pre, img);
        // ColorRanges = getColorRange (myStandards, threshold);
        // cv::Rect boundingrect;

        // for (int i = 0; i < ColorRanges.size (); i++)
        // {
        //     boundingrect = Aim (img, ColorRanges[i]);
        //     cv::rectangle (img, boundingrect, cv::Scalar (0, 255, 255), 2);
        //     cv::circle (img, cv::Point (boundingrect.tl ().x + 15, boundingrect.tl ().y - 15), 25, cv::Scalar (0, 200, 255), cv::FILLED);
        //     cv::putText (img, std::to_string (i), boundingrect.tl (), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar (255, 255, 255), 3);
        //     cv::Point p = getCenter (boundingrect);
        //     log (p);
        // }

        // cv::imshow ("Img", img);
        // cv::imshow ("ImgPre", img_pre);
        if (cv::waitKey (20) == 27)
        {
            break;
        }

    }
 
    return 0;
}
