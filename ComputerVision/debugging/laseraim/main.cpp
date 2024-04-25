#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

// int main ()
// {
// 	cv::VideoCapture cap ("../laser2.mp4");
// 	cv::Mat img, imgHSV, mask;
// 	
//     int h_u = 179, h_l = 58, s_u = 133, s_l = 0, v_u = 255, v_l = 229;
// 
//     cv::namedWindow ("Track Bar");
//     cv::createTrackbar ("Hue Max", "Track Bar", &h_u, 179);
//     cv::createTrackbar ("Hue Min", "Track Bar", &h_l, 179);
//     cv::createTrackbar ("Saturation Max", "Track Bar", &s_u, 255);
//     cv::createTrackbar ("Saturation Min", "Track Bar", &s_l, 255);
//     cv::createTrackbar ("Value Max", "Track Bar", &v_u, 255);
//     cv::createTrackbar ("Value Min", "Track Bar", &v_l, 255);
// 
//     int key = 0;
// 
// 	while (true)
// 	{
// 		cv::Scalar lower (h_l, s_l, v_l), upper (h_u, s_u, v_u);
// 		cap.read (img);
// 		cv::cvtColor (img, imgHSV, cv::COLOR_BGR2HSV);
// 		
// 		cv::inRange (imgHSV, lower, upper, mask);
// 		cv::imshow ("Mask", mask);
// 		key = cv::waitKey (33);
// 
// 		if (key == 27)
// 		{
// 			break;
// 		}
// 	}
// 
// 	return 0;
// 	
// }


int main ()
{
	cv::VideoCapture cap ("../laser2.mp4");
	cv::Mat img, imgHSV, mask;
    int h_u = 179, h_l = 58, s_u = 133, s_l = 0, v_u = 255, v_l = 229;
	cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (3, 3));

	cv::Scalar upper (h_u, s_u, v_u), lower (h_l, s_l, v_l);
	while (true)
	{
		cap.read (img);
		if (img.empty ())
		{
			continue;
		}
		cv::cvtColor (img, imgHSV, cv::COLOR_BGR2HSV);
		cv::inRange (imgHSV, lower, upper, mask);
		cv::erode (mask, mask, kernel);
		cv::dilate (mask, mask, kernel);

		
		std::vector <std::vector <cv::Point>> contours;
		std::vector <cv::Rect> results;
		cv::findContours (mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < contours.size (); i++)
		{
			cv::Rect bbox = cv::boundingRect (contours[i]);
			if (bbox.area () < 10000)
			{
				// results.push_back (bbox);
				cv::rectangle (img, bbox, cv::Scalar (255, 255, 0), 1);
			}
		}
		cv::imshow ("img", img);
		if (cv::waitKey (33) == 27)
		{
			break;
		}
		
	}

}
