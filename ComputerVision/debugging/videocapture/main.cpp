#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

int main ()
{
	cv::Mat img;
	cv::VideoCapture cap (0);
	cv::VideoWriter writer ("../videos/laser2.mp4", cv::VideoWriter::fourcc ('M', 'J', 'P', 'G'), 30.0, cv::Size (640, 480));

	while (true)
	{
		cap.read (img);
		cv::imshow ("Img", img);
		writer.write (img);
		if (cv::waitKey (33) == 27)
		{
			break;
		}
	}
}
