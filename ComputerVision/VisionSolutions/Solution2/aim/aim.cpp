#include "aim.h"
#include <cstring>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// void aimming (cv::Mat img, std::vector <Result> target, int num, cv::Scalar lower, cv::Scalar upper)
// {
// 	cv::Mat toaim;
// 	img.copyTo (toaim);
// 	cv::circle (toaim, cv::Point (120, 500), 5, cv::Scalar (0, 0, 255), cv::FILLED);
// 	log ("Aimming target " << num);
// 	int condition = 1, delta = 5;
// 	cv::Mat imgMask = preprocess (toaim, lower, upper);
// 	cv::Rect bbox = gettarget (imgMask);
// 	cv::rectangle (toaim, bbox, cv::Scalar (255, 255, 0), 1);
// 	cv::Point his = cv::Point (bbox.x + bbox.width * 0.5, bbox.y + bbox.height * 0.5);
// 	cv::Point tp (target[1].bbox.x + target[1].bbox.width * 0.5, target[1].bbox.y + target[1].bbox.height * 0.5);
// 	int dx = tp.x - his.x;
// 	int dy = tp.y - his.y;
// 	cv::imshow ("Aim", toaim);
// 	cv::waitKey (20);
// 	while (condition)
// 	{
// 		cv::Mat to_aim;
// 		img.copyTo (to_aim);
// 		cv::Point newp (his.x + 0.1 * dx, his.y + 0.1 * dy);
// 		cv::circle (to_aim, newp, 5, cv::Scalar (0, 0, 255), cv::FILLED);
// 		cv::imshow ("Aim", to_aim);
// 		cv::waitKey (20);
// 		cv::Mat imgMask = preprocess (to_aim, lower, upper);
// 		cv::Rect bbox = gettarget (imgMask);
// 		cv::Point now (bbox.x + bbox.width * 0.5, bbox.y + bbox.height * 0.5);
// 		his = now;
// 		if (bbox.empty ())
// 		{
// 			log ("Lost Laser Target !");
// 			return ;
// 		}
// 		if (abs (tp.x - newp.x) < 50  and abs (tp.y - newp.y) < 50)
// 		{
// 			condition = 0;
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
int daimming (int fd, cv::VideoCapture cap, cv::Rect target, cv::Scalar lower, cv::Scalar upper)
{
	float standard = 2;
	cv::Mat img;
	cv::Point targetp (target.x + target.width * 0.5, target.y + target.height *0.5);
	while (true)
	{
		// get the laser
		cap.read (img);
		cv::Mat imgMask;
		// imgMask = preprocess (img, lower, upper);
		// cv::Rect bbox = gettarget (imgMask);
		cv::Rect laser;
		int is_su = getlaser (img, upper, lower, laser);
		cv::rectangle (img, laser, cv::Scalar (255, 0, 0), 1);
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
		data tosend;
		strcpy (tosend.to_send, to_send.c_str ());
		write (fd, &tosend, sizeof (tosend));

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
