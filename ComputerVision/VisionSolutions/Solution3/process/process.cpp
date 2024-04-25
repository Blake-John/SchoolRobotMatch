#include "process.h"

/**
 * @brief 预处理图片
 *
 * @param img 传入的图片
 * @return 处理后的结果
 */
cv::Mat preprocess (cv::Mat img)
{
	cv::Mat imgblur, imgbila, imgshift, imgHSV, mask, imgadd;
	// cv::medianBlur (img,imgblur, 3);
	//cv::bilateralFilter (img, imgbila, 0, 32, 23);
	cv::pyrMeanShiftFiltering (img, imgshift, 25, 10);
	// cv::addWeighted (imgbila, 0.5, imgshift, 0.5, 10, imgadd);

	return imgshift;
	
}
