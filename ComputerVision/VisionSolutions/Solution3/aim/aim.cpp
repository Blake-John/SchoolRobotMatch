#include "aim.h"
#include "func.h"
#include "serial.h"
#include "process.h"
#include <cstring>
#include <opencv2/core/persistence.hpp>
#include <opencv2/videoio.hpp>

// void aimming (cv::VideoCapture cap, std::vector <Result> target, int num, cv::Scalar laser_lower, cv::Scalar laser_upper, int fd)
// {
// 	cv::Mat img;
// 	cv::Rect laser;
// 
// 	int is_su = 0;
// 	while (true)
// 	{
// 		cap.read (img);
// 		is_su = getlaser (img,laser_upper, laser_lower, laser);
// 		if (is_su == 1)
// 		{
// 			break;
// 		}
// 		else if (is_su == 0)
// 		{
// 			data to_send;
// 			std::string to_senddata = "X2Y2";
// 			strcpy (to_send.to_send, to_senddata.c_str ());
// 			write (fd, &to_send, sizeof (to_send));
// 		}
// 	}
// 
// 
// 	cv::Point his = cv::Point (laser.x + laser.width * 0.5, laser.y + laser.height * 0.5);
// 	while (1)
// 	{
// 		for (int i = 0; i < target.size (); i++)
// 		{
// 			cv::Point tp (target[i].bbox.x + target[i].bbox.width * 0.5, target[i].bbox.y + target[i].bbox.height * 0.5);
// 			YawPitch (his, tp, C);
// 		}
// 	}
// }

/**
 * @brief 动态通过追踪激光实现动态瞄准
 *
 * @param fd 串口文件描述符
 * @param cap 相机对象
 * @param target 待瞄准的对象位置信息
 * @param lower 激光色域下界
 * @param upper 激光色域上界
 * @return 成功返回 1, 失败返回 0
 */
int daimming (int fd, cv::VideoCapture cap, cv::Rect target, cv::Scalar laser_lower, cv::Scalar laser_upper)
{
	float standard = 4;
	cv::Mat img;
	cv::Point targetp (target.x + target.width * 0.5, target.y + target.height *0.5);
	data sending;
	std::string init = "X10Y15";
	strcpy (sending.to_send, init.c_str ());
	write (fd, &sending, sizeof (sending));

	while (true)
	{
		// get the laser
		cap.read (img);
		cv::Mat imgMask;
		int is_su;
		cv::Rect laser;
		is_su = getlaser (img, laser_upper, laser_lower, laser);
		// imgMask = preprocess (img);
		cv::imshow ("Cam", img);
		if (cv::waitKey (33) == 27)
		{
			return 0;
		}
		if (laser.empty ())
		{
			// if find no laser, then continue, find the laser again
			continue;
		}

		cv::Point laser_center (laser.x + laser.width * 0.5, laser.y + laser.height * 0.5);
		if (abs (targetp.x - laser_center.x) < 30 and abs (targetp.y - laser_center.y) < 30)
		{
			break;
		}
		
		// calculate the difference
		float dx = targetp.x - laser_center.x;
		float dy = targetp.y - laser_center.y;
		float angle_x, angle_y;
		
		if (dx != 0)
		{
			angle_x = standard * abs (dx) / dx;
			angle_y = standard * dy / abs (dx);
		}
		else if (dy != 0)
		{
			angle_x = standard * dx / abs (dy);
			angle_y = standard * abs (dy) / dy;
		}
		
		std::string to_send = "@X" + std::to_string (angle_x) + "Y" + std::to_string (angle_y) + "\n";
		strcpy (sending.to_send, to_send.c_str ());
		write (fd, &sending, sizeof (sending));
	}
	return 1;
}

/**
 * @brief 在等待激光瞄准2s的同时保证相机正常传输图片
 *
 * @param cap 相机对象
 */
void waitfor (cv::VideoCapture cap)
{
	cv::Mat img;
	int time = 0;
	while (true)
	{
		cap.read (img);
		cv::imshow ("Cam", img);
		cv::waitKey (20);
		time += 20;
		if (time >= 2000)
		{
			break;
		}
	}
}

