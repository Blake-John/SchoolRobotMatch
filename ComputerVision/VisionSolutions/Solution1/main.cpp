/**
 * @file main.cpp
 * @author Blake John (2991151588@qq.com)
 * @brief the function to show the mid-term assessment
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 * @attention 此次考核使用图片进行展示，因为放假回老家搓了一个板，但忘记录个视频了，板带不走
 * 
 */

#include "mathfunc.h"
#include "serial.h"
#include <cstring>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <termios.h>
#include <unistd.h>

/// @brief 所有分类的名称
// std::vector <std::string> Classes = {"blake", "y_l", "y_d", "blue", "pink", "red", "orange", "green", "purple"};

// #define log(x) std::cout << x << std::endl;

int main ()
{
	// 初始化
	cv::Mat imgTarget;
	std::string modelpath = "../model/v3tiny-objs-1514.onnx";
	int fd = SerialInit ("/dev/ttyUSB0");
	int key = SerialSetting (fd, B115200, CS8);
	cv::VideoCapture cap (2);
	// cap.set (cv::CAP_PROP_FRAME_WIDTH, 1280);
	// cap.set (cv::CAP_PROP_FRAME_HEIGHT, 720);
	cv::Mat img;

	if (key == 1)
	{
		log ("Initialze Port Successfully !");
	}
	else
	{
		log ("Initialize Port ERROR !");
		return 0;
	}

	Yolo detector (modelpath);
	std::vector <Result> result;
	std::vector <std::vector <Result>> target;

	// 检测图像
	imgTarget = cv::imread ("../imgs/6.jpg");
	// cv::Mat img;
	detector.Detect (imgTarget, result);

	// 获取标准区色块
	order (result, target);

	std::vector <double> angles;

	// 记录上一次瞄准的点
	cv::Point history;
	history = C;
	int time = 0, count = 0, to_aim = 1;
	data d_tosend;
	cv::Mat imgshow;
	imgTarget.copyTo (imgshow);
	d_tosend.end = '\n';
	// strcpy (d_tosend.to_send, "RESET");
	d_tosend.to_send[0] = 'R';
	d_tosend.to_send[1] = 'E';
	d_tosend.to_send[2] = 'S';
	d_tosend.to_send[3] = 'T';
	d_tosend.to_send[4] = '\n';
	write (fd, &d_tosend, sizeof (d_tosend));
	// write (fd, )
	char end_ = '\n';
	write (fd, &end_, 1);
	sleep (2);
	d_tosend.end = '\n';
	int keys = 0;
	while (true)
	{
		// if (keys == 0)
		// {
		// 	keys++;
		// 	count++;
		// 	continue;
		// }
		cap.read (img);
		// log ("cam : " << img.size () << " " << "target : " <<imgTarget.size ());
		cv::resize (imgTarget, imgTarget,cv::Size (640, 480));
		cv::addWeighted (img, 0.5, imgTarget, 0.5, 0, img);
		if (to_aim)
		{
			imgTarget.copyTo (imgshow);
			cv::Point center (target[count][1].bbox.x + 0.5 * target[count][1].bbox.width, target[count][1].bbox.y + 0.5 * target[count][1].bbox.height);
			cv::circle (imgshow, center, 5, cv::Scalar (0, 0, 255), cv::FILLED);
			angles = YawPitch (history, center);
			history = center;
			std::string tosend = "X" + std::to_string (angles[0]) + "Y" + std::to_string (angles[1]);
			strcpy (d_tosend.to_send, tosend.c_str ());
			int writebyte = 0;
			writebyte = write (fd, &d_tosend, sizeof (d_tosend));
			log (tosend);
			log ("Write " << writebyte << " of data to stm32 !");
			to_aim = 0;
		}
		
		cv::imshow ("Cam", img);
		cv::imshow ("Target", imgshow);
		cv::waitKey (20);
		time += 20;
		if (time == 2000)
		{
			to_aim = 1;
			count++;
			time = 0;
		}
		if (count > 4)
		{
			break;
		}
		
	}
	// senddata (fd, "@\t");
	closeserial (fd);

}
