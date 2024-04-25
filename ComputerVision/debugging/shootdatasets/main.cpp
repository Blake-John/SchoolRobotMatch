#include <opencv2/core/persistence.hpp>
#include <opencv2/videoio.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <iostream>

int main ()
{
	cv::Mat img;
	cv::VideoCapture cap (2);
	// cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);
	// cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);
	int count = 730, key = 0, time = 0;
	std::string root_path = "./imgs/";
	std::string path;
	std::cin.get ();

	while (true)
	{
		cap.read (img);
		cv::imshow ("Cam", img);
		key = cv::waitKey (20);
		time += 20;

		if (key == 27)
		{
			break;
		}

		if (time == 100)
		{
			path = root_path + std::to_string (count) + ".jpg";
			cv::imwrite (path, img);
			count++;
			time = 0;
		}
	}

	return 0;
}
