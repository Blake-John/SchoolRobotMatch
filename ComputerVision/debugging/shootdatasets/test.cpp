#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

int main ()
{
	cv::Mat img;
	cv::VideoCapture cap (2);
	cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);
	cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);

	while (true)
	{
		cap.read (img);
		cv::imshow ("Cam", img);
		if (cv::waitKey (20) == 27)
		{
			break;
		}
	}

	return 0;
}
