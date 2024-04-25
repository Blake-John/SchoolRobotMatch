#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

int main ()
{
	int bright = 0;
	int exposure = 0;
    cv::namedWindow ("Track Bar");
    cv::createTrackbar ("bright", "Track Bar", &bright, 1000);
    cv::createTrackbar ("exposure", "Track Bar", &exposure, 1000);

	cv::VideoCapture cap (0);

	cv::Mat img;

	while (true)
	{
		cap.set (cv::CAP_PROP_BRIGHTNESS, 0);
		cap.read (img);
		cv::imshow ("Cam", img);
		cv::waitKey (33);
	}
}
