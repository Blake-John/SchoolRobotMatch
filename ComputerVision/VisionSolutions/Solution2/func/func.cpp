#include "func.h"
#include <opencv2/imgproc.hpp>
#include <string>

/**
 * @brief 预处理图片，用于获取目标的轮廓
 *
 * @param img_in 传入的图片
 * @param lower 色域下界
 * @param upper 色域上界
 * @return 返回二值图
 */
cv::Mat preprocess (cv::Mat img_in, cv::Scalar lower, cv::Scalar upper)
{
	cv::Mat imgHSV, imgMask;
	cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (3, 3));
	cv::cvtColor (img_in, imgHSV, cv::COLOR_BGR2HSV);
	cv::inRange (imgHSV, lower, upper, imgMask);
	cv::dilate (imgMask, imgMask, kernel);
	return imgMask;
}

/**
 * @brief 获取目标位置信息
 *
 * @param imgMask 传入的二值图
 * @return 返回包裹目标的矩形框
 */
cv::Rect gettarget (cv::Mat imgMask)
{
	cv::Rect bbox;
	std::vector <std::vector <cv::Point>> contours;
	cv::findContours (imgMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	cv::drawContours (imgMask, contours, -1, cv::Scalar (255, 255, 0), 2);
	bbox = cv::boundingRect (contours[0]);
	return bbox;
}

/**
 * @brief 获取激光位置信息
 *
 * @param img 传入的图片
 * @param laser_upper 激光色域下界
 * @param laser_lower 激光色域上界
 * @param laser 用于存放激光位置信息的矩形
 * @return 成功找到激光返回 1, 失败返回 0
 */
int getlaser (cv::Mat img, cv::Scalar laser_upper, cv::Scalar laser_lower, cv::Rect laser)
{
	cv::Mat imgHSV, mask;
	cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (3, 3));
	std::vector <std::vector< cv::Point>> contours;
	std::vector <cv::Rect> bboxes;

	cv::cvtColor (img, imgHSV, cv::COLOR_BGR2HSV);
	cv::inRange (imgHSV, laser_lower, laser_upper, mask);
	cv::erode (mask, mask, kernel);
	cv::dilate (mask, mask, kernel);
	cv::findContours (mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	if (contours.size () != 0)
	{
		for (int i = 0; i < contours.size (); i++)
		{
			cv::Rect bbox = cv::boundingRect (contours[i]);
			if (bbox.area () < 500)
			{
				bboxes.push_back (bbox);
			}
		}
		laser = bboxes[0];
		return 1;
	}
	else
	{
		log ("lost laser !");
		return 0;
	}

}

/**
 * @brief 画出检测结果
 *
 * @param img 用于绘画的图片
 * @param target 检测的结果
 */
void drawresult (cv::Mat img, std::vector <std::vector <Result>> target)
{
	for (int i = 0; i < target.size (); i++)
	{
		cv::rectangle (img, target[i][0].bbox, cv::Scalar (255, 255, 0), 2);
		cv::rectangle (img, target[i][1].bbox, cv::Scalar (255, 255, 0), 2);
		cv::putText (img, std::to_string (i), cv::Point (target[i][1].bbox.x, target[i][1].bbox.y - 5), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar (255, 0, 0), 1);
	}
}

/**
 * @brief 对获取的所有矩形框通过坐标进行排序，向量前五个即为标准区的目标
 * 
 * @param result 输入的检测结果集合的引用，用于获取标准区
 * @param target 用于存储标准区的物体的变量的引用
 */
void order (std::vector <Result> &result, std::vector <std::vector <Result>> &target)
{

    // order by y
    for (int i = 0; i < result.size () - 1; i++)
    {
        for (int j = 0; j < result.size () - i - 1; j++)
        {
            if (result[j].bbox.y > result[j + 1].bbox.y)
            {
                Result temp;
                temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
                        
        }
        
    }
    
    // order by x
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (result[j].bbox.x > result[j + 1].bbox.x)
            {
                Result temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
            
        }
        
    }
    
    // get the first five result stored in result
    for (int i = 0; i < 5; i++)
    {
        for (int j = 5; j < result.size (); j++)
        {
            if (result[i].classid == result[j].classid)
            {
                target.push_back ({result[i], result[j]});
            }
        }
    }
    
}

