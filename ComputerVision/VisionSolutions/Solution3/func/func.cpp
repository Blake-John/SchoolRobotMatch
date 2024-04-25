#include "func.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

/**
 * @brief 通过色域来获取目标及其位置信息
 *
 * @param imgPre 传入的经过预处理的图片
 * @param colorranges 目标颜色阈值
 * @return 存放结果的向量
 */
std::vector <Result> gettarget (cv::Mat imgPre, std::vector <std::vector <int>> colorranges)
{
	cv::Mat imgHSV, mask;
	cv::Rect bbox;
	std::vector <std::vector <cv::Point>> contours;
	std::vector <Result> results;
	Result result;
	cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (5, 5));

	cv::cvtColor (imgPre, imgHSV, cv::COLOR_BGR2HSV);

	for (int i = 0; i < colorranges.size (); i++)
	{
		cv::Scalar upper (colorranges[i][0], colorranges[i][1], colorranges[i][2]);
		cv::Scalar lower (colorranges[i][3], colorranges[i][4], colorranges[i][5]);
		cv::inRange (imgHSV, lower, upper, mask);
		cv::erode (mask, mask, kernel);
		cv::dilate (mask, mask, kernel);
		cv::findContours (mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		for (int j = 0; j < contours.size (); j++)
		{
			cv::Rect bbox = cv::boundingRect (contours[j]);
			if (bbox.area () >= 200 and bbox.area () <= 20000)
			{
				result.bbox = bbox;
				result.classid = i;
				results.push_back (result);
			}
			
		}

	}

	return results;
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
void drawresult (cv::Mat img, std::vector <Result> piece_results)
{
	for (int i = 0; i < piece_results.size (); i++)
	{
		cv::rectangle (img, piece_results[i].bbox, cv::Scalar (255, 255, 0), 2);
		cv::putText (img, std::to_string (piece_results[i].classid),\
				cv::Point (piece_results[i].bbox.x, piece_results[i].bbox.y - 10),\
				cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar (255, 255, 0), 1);
	}
}

/**
 * @brief 对获取的所有矩形框通过坐标进行排序，向量前五个即为标准区的目标
 * 
 * @param result 输入的检测结果集合的引用，用于获取标准区
 * @param target 用于存储标准区的物体的变量的引用
 */
void order (std::vector <Result> &result, std::vector <Result> &target)
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
                target.push_back (result[j]);
            }
        }
    }
    
}


