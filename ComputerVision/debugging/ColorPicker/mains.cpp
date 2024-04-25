#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>


int main ()
{
    cv::Mat img, imgHSV, mask, imgbila, imgshift, imgadd;
    int h_u = 179, h_l = 0, s_u = 255, s_l = 0, v_u = 255, v_l = 0;

    cv::namedWindow ("Track Bar");
    cv::createTrackbar ("Hue Max", "Track Bar", &h_u, 179);
    cv::createTrackbar ("Hue Min", "Track Bar", &h_l, 179);
    cv::createTrackbar ("Saturation Max", "Track Bar", &s_u, 255);
    cv::createTrackbar ("Saturation Min", "Track Bar", &s_l, 255);
    cv::createTrackbar ("Value Max", "Track Bar", &v_u, 255);
    cv::createTrackbar ("Value Min", "Track Bar", &v_l, 255);

    int key = 0;
    std::fstream file ("../ColorRange.txt", std::ios::trunc | std::ios::out);

	img = cv::imread ("../imgs/434.jpg");
	cv::bilateralFilter (img, imgbila, 0, 32, 23);
	cv::imshow ("Bila", imgbila);

	cv::pyrMeanShiftFiltering (img, imgshift, 25, 12);
	cv::imshow ("Shift", imgshift);

	cv::addWeighted (imgbila, 0.5, imgshift, 0.5, 10, imgadd);
	cv::imshow ("Add", imgadd);
	cv::cvtColor (imgadd, imgHSV, cv::COLOR_BGR2HSV);

	while (true)
	{
		cv::Scalar lower (h_l, s_l, v_l), upper (h_u, s_u, v_u);
		cv::inRange (imgHSV, lower, upper, mask);
		cv::imshow ("Mask", mask);
		key = cv::waitKey (20);

		if (key == 27)
		{
			break;
		}
		else if (key == 49)
		{
            file << h_u << '\n' << s_u << '\n' << v_u << '\n';
            file << h_l << '\n' << s_l << '\n' << v_l << '\n' << '\n';
		}
	}
	file.close ();

	return 0;
}
