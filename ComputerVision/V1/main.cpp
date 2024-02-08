#include "yolo.h"
#include "mathfunc.h"



int main ()
{
    std::vector <cv::Rect> result;
    std::vector <cv::Rect> standard;
    std::string modelpath = "../yolov3-tiny-1000.onnx";
    Yolo yolodetector (modelpath);
    cv::VideoCapture cap (1);
    cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);
    cv::Mat img, img2, img3;

    std::cout << "Please choose your mode in the loop :" << std::endl;
    // std::cout << "0 prepare to aimming" << std::endl;
    std::cout << "1 start aimming" << std::endl;
    std::cout << "2 restart aimming" << std::endl;

    img = cv::imread ("../0.jpg");
    img.copyTo (img2);
    img.copyTo (img3);
    yolodetector.Detect (img, result);
    getStandard (result, standard);
    for (int i = 0; i < standard.size (); i++)
    {
        cv::rectangle (img2, standard[i], cv::Scalar (255, 255, 0), 2);
        cv::putText (img2, std::to_string (i), cv::Point (standard[i].x, standard[i].y), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar (255, 0, 0), 1);
    }
    cv::imshow ("Img2", img2);
    for (int i = 0; i < 5; i++)
    {
        Aim (img3, standard, i);
        cv::waitKey (0);
    }
    
    
}



// int main ()
// {
//     std::vector <cv::Rect> result;
//     std::vector <cv::Rect> standard;
//     // int color_threshold = 10;
//     std::string modelpath = "../yolov3-tiny-1000.onnx";
//     Yolo yolodetector (modelpath);
//     cv::VideoCapture cap (1);
//     cv::Mat img, img2;

//     std::cout << "Please choose your mode in the loop :" << std::endl;
//     // std::cout << "0 prepare to aimming" << std::endl;
//     std::cout << "1 start aimming" << std::endl;
//     std::cout << "2 restart aimming" << std::endl;
//     int key1 = 0, key2 = 0;
//     int aimkey = 0;
//     clock_t s, e;
//     double count = 0.0;
//     while (1)
//     {
//         cap.read (img);
//         img.copyTo (img2);
//         // yolodetector.detect (img, result);
//         yolodetector.Detect (img, result);
//         for (int i = 0; i < result.size (); i++)
//         {
//             cv::rectangle (img2, result[i], cv::Scalar (255, 255, 0), 2);
//         }
//         cv::imshow ("Img", img2);
//         key1 = cv::waitKey (20);
//         if (key1 == 49 or 50)
//         {
//             key2 = key1;
//             key1 = 0;
//         }
//         if (key2 == 49)
//         {
//             // s = clock ();
//             getStandard (result, standard);
//             std::cout << standard.size () << std::endl;
//             Aim (img, standard, aimkey);
//             // e = clock ();
//             // std::cout << (double)(e - s) << std::endl;
//             // count += (double)(e - s);
//             // if (count > 2.0)
//             // {
//             //     count = 0.0;
//             //     aimkey += 1;
//             //     if (aimkey > 4)
//             //     {
//             //         aimkey = 0;
//             //         key2 = 0;
//             //     }
//             // }
            
//         }
//         else if (key2 == 50)
//         {
//             std::cout << "Reset" << std::endl;
//             key2 = 0;
//             aimkey = 0;
//             count = 0.0;
//         }

//         if (key1 == 27)
//         {
//             break;
//         }

//         result.clear ();
//         standard.clear ();
//     }

//     if (cv::waitKey (0) == 27)
//     {
//         std::exit (0);
//     }

//     return 0;
// }

// int main ()
// {
//     std::vector <cv::Rect> result;
//     std::vector <cv::Rect> standard;
//     std::string modelpath = "../yolov3-tiny-1000.onnx";
//     Yolo yolodetector (modelpath);
//     cv::VideoCapture cap (1);
//     cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);
//     cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);
//     cv::Mat img, img2, img3;

//     std::cout << "Please choose your mode in the loop :" << std::endl;
//     // std::cout << "0 prepare to aimming" << std::endl;
//     std::cout << "1 start aimming" << std::endl;
//     std::cout << "2 restart aimming" << std::endl;

//     int key = 0;
//     while (1)
//     {
//         cap.read (img);
//         img.copyTo (img2);
//         img.copyTo (img3);
//         yolodetector.Detect (img, result);
//         for (int i = 0; i < result.size (); i++)
//         {
//             cv::rectangle (img2, result[i], cv::Scalar (255, 255, 0), 2);
//         }
//         cv::imshow ("Result", img2);

//         key = cv::waitKey (20);
//         if (key == 49)
//         {
//             getStandard (result, standard);
//             for (int i = 0; i < 1; i++)
//             {
//                 cv::rectangle (img3, standard[i], cv::Scalar (255, 255, 0), 2);
//                 cv::Point pt (standard[i].x + (int)(standard[i].width * 0.5), standard[i].y + (int)(standard[i].height * 0.5));
//                 cv::circle (img3, pt, 4, cv::Scalar (255, 0, 0), -1);
//             }
//             cv::imshow ("Standard", img3);
//             Aim (img, standard, 0);
//         }
//         if (key == 27)
//         {
//             break;
//         }
        
//         result.clear ();
//         standard.clear ();
//     }
    
// }