#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main ()
{
	cv::Mat img, imgGaussian, imgBlur, imgShift, imgMedian, imgBilateral;
	int GaussianKernel = 1, GaussianSigmax = 1, GaussianSigmay = 1, BlurKernel = 1, MedianKernel = 1, Shift_color = 0,\
						 Shift_space = 0, Bilateral_color = 0, Bilateral_space = 0, Bilateral_d = 0;

	
	img = cv::imread ("../15.jpg");
	// cv::resize (img, img, cv::Size (), 0.3, 0.3);
	cv::imshow ("Img", img);

	// Track bar
	cv::namedWindow ("Trackbar");
	cv::createTrackbar ("BlurKernel", "Trackbar", &BlurKernel, 11);
	cv::createTrackbar ("GaussianKernel", "Trackbar", &GaussianKernel, 11);
	cv::createTrackbar ("GaussianSigmax", "Trackbar", &GaussianSigmax, 50);
	cv::createTrackbar ("GaussianSigmay", "Trackbar", &GaussianSigmay, 50);
	cv::createTrackbar ("MedianKernel", "Trackbar", &MedianKernel, 11);
	cv::createTrackbar ("bilateral_d", "Trackbar", &Bilateral_d, 50);
	cv::createTrackbar ("Bilateral_color", "Trackbar", &Bilateral_color, 255);
	cv::createTrackbar ("Bilateral_space", "Trackbar", &Bilateral_space, 300);
	cv::createTrackbar ("Shift_space", "Trackbar", &Shift_space, 300);
	cv::createTrackbar ("Shift_color", "Trackbar", &Shift_color, 255);
	

	while (true)
	{
		cv::blur (img, imgBlur, cv::Size (BlurKernel, BlurKernel));
		cv::GaussianBlur (img, imgGaussian, cv::Size (2 * GaussianKernel - 1, 2 * GaussianKernel - 1), (double)GaussianSigmax / 10.0, (double)GaussianSigmay / 10.0);
		cv::medianBlur (img, imgMedian, 2 * MedianKernel - 1);
		cv::bilateralFilter (img, imgBilateral, Bilateral_d, Bilateral_color, Bilateral_space);
		cv::pyrMeanShiftFiltering (img, imgShift, Shift_space, Shift_color);

		cv::imshow ("Gauss", imgGaussian);
		cv::imshow ("Blur", imgBlur);
		cv::imshow ("Median", imgMedian);
		cv::imshow ("Bilateral", imgBilateral);
		cv::imshow ("shift", imgShift);

		if (cv::waitKey (20) == 27)
		{
			break;
		}
	}

}
