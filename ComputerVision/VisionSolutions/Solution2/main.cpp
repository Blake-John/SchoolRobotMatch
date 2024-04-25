/**
 * @file main.cpp
 * @author Blake John (2991151588@qq.com)
 * @brief the function to aim the target by the given orders
 * @version 0.1
 * @date 2024-04-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "func.h"
#include "yolo.h"
#include "aim.h"
#include "serial.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int colorrange[6] = {73, 255, 255, 0, 175, 194};
cv::Scalar upper (73, 255, 255), lower (0, 175, 194);

int main ()
{
	cv::Mat img, imgMask;
	cv::Rect bbox;
	std::vector <Result> result;
	std::vector <std::vector <Result>> target;

	cv::VideoCapture cap (0);
	std::string modelpath = "../model/true_tar_finnal.onnx";
	std::string serialtarget = "/dev/ttyUSB0";
	std::string imgpath = "../imgs/1.jpg";

	
	// cap.read (img);
	// Initialize the network
	Yolo yolodetector (modelpath);

	int key = 0;
	int fd = 0;

	fd = SerialInit (serialtarget.c_str ());
	if (fd != -1)
	{
		SerialSetting (fd, B115200, CS8);
	}
	else
	{
		log ("Please reprepare !");
	}

	while (true)
	{
		log ("Please choose the function : ");
		log ("0 get the target and prepare to aim");
		log ("1 start aimming");
		std::cin >> key;
		if (key == 0)
		{
			while (true)
			{
				cap.read (img);
				int waitkey = cv::waitKey (20);
				if (waitkey == 49)
				{
					cv::destroyWindow ("Cam");
					break;
				}
				else if (waitkey == 48)
				{
					if (!result.empty () and !target.empty ())
					{
						result.clear ();
						target.clear ();
						
					}
					cv::pyrMeanShiftFiltering (img, img, 15, 5);
					yolodetector.Detect (img, result);
					if (!result.empty ())
					{
						order (result, target);
						drawresult (img, target);
						cv::imshow ("Target", img);
					}
				}
				cv::imshow ("Cam", img);
			}
			// Initialize the serialport
			
			// // get the order
			// cv::Mat targetshow;
			// cap.read (targetshow);
			// yolodetector.Detect (targetshow, result);
			// order (result, target);
			// drawresult (targetshow, target);
			// log ("Get the target successfully !");

			// // show the result
			// cv::namedWindow ("Target");
			// cv::imshow ("Target", targetshow);
			// cv::waitKey (10);

			// // // Open the Laser
			// // log ("Opening the Laser ... ");
			// // senddata (fd, "@OpenLaser\t");
			// // int readkey = 1;
			// // while (readkey) {
			// // 	usleep (300);
			// // 	char buffer[50];
			// // 	readkey = read (fd, buffer, sizeof (buffer));
			// // 	if (readkey == -1)
			// // 	{
			// // 		if (errno == EAGAIN) //* 如果错误为 阻塞 ，即没有数据，则跳过
			// // 		{
			// // 			usleep (100);
			// // 			continue;
			// // 		}
			// // 		else
			// // 		{
			// // 			log ("ERROR !");
			// // 			log (errno);
			// // 			return 1;
			// // 		}
			// // 	}
			// // 	else
			// // 	{
			// // 		log (buffer);
			// // 		break;
			// // 	}
			// // }
			// while (true)
			// {
			// 	cap.read (img);
			// 	cv::Mat imgMask = preprocess (img, lower, upper);
			// 	cv::Rect laser = gettarget (imgMask);
			// 	if ( !laser.empty ())
			// 	{
			// 		log ("Get the Laser Successfully !");
			// 		cv::rectangle (img, laser, cv::Scalar (255, 255, 0), 1);
			// 		cv::imshow ("Laser", img);
			// 		break;
			// 	}
			// 	else
			// 	{
			// 		log ("Get the Laser Failed !");
			// 		log ("Trying Again...")
			// 	}
			// }

			// while (cv::waitKey (20) != 27);
			// cv::destroyWindow ("Target");
			// cv::destroyWindow ("Laser");
		}
		else if (key == 1)
		{
			int num = 0;
			while (num < 5)
			{
				// aimming (img, target[num], num, lower, upper);
				log ("Aimming Target " << num);
				int is_success = daimming (fd, cap, target[num][1].bbox, lower, upper);
				if (is_success == 1)
				{
					log ("Aimming Target " << num << "successfully !");
				}
				else if (is_success == 0)
				{
					log ("Aimming Target Interrupted !");
					log ("return to reaimming...");
					break;
				}
				waitfor (cap);
				num++;
			}
			if (num > 5)
			{
				log ("Aimming Finished !");
			}
			senddata (fd, "@\t");


			log ("Exit Aimming !");
		}
		else
		{
			log ("Input ERROR ! Please Reinput !");
		}
	}

	// imgMask = preprocess (img, lower, upper);
	// bbox = gettarget (imgMask);
	// cv::rectangle (img, bbox, cv::Scalar (255, 255, 0), 1);

	// int condition = 1;

	// cv::imshow ("Img", img);
	// cv::waitKey (0);
	closeserial (fd);
	return 0;
}
