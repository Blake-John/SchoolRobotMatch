/**
 * @file main.cpp
 * @author Blake John (2991151588@qq.com)
 * @brief the function to aim the target by given orders
 * @version 0.1
 * @date 2024-04-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "func.h"
#include "process.h"
#include "serial.h"
#include "aim.h"
#include <cstring>
#include <opencv2/highgui.hpp>
#include <vector>

int colorrange[6] = {179, 133, 255, 58, 0, 229};
// int colorange[][6] = {{179, 56, 104, 0, 15, 50}, {109, 59, 173, 66, 0, 141}, {18, 219, 189, 0, 165, 151}, {179, 191, 193, 133, 77, 153},\
// 	{82, 172, 134, 41, 80, 96}, {179, 209, 185, 148, 125, 86}, {26, 191, 181, 17, 140, 154}, {129, 211, 131, 94, 58, 51}, {39, 176, 198, 27, 138, 146}, {29, 89, 80, 19, 50, 54}};
std::vector <std::vector <int>> colorranges = {{179, 99, 123, 140, 0, 31}, {109, 82, 213, 57, 9, 148}, {18, 219, 189, 0, 165, 151}, {179, 128, 225, 144, 51, 144},\
	{79, 178, 194, 43, 92, 115}, {179, 255, 199, 151, 121, 100}, {26, 202, 188, 15, 140, 139}, {122, 227, 136, 91, 95, 71}, {39, 148, 211, 25, 106, 174}, {45, 170, 90, 9, 16, 5}};
cv::Scalar laser_upper (73, 255, 255), laser_lower (0, 175, 194);

int main ()
{
	cv::Mat img, imgMask, imgPre;
	cv::Rect bbox;
	Result result;
	std::vector <Result> piece_results;
	std::vector <Result> target;

	cv::VideoCapture cap (2);
	std::string serialtarget = "/dev/ttyUSB0";

	
	// cap.read (img);

	int key = 0;
	int fd = 0;


	while (true)
	{
		log ("Please choose the function : ");
		log ("0 get the target and prepare to aim");
		log ("1 start aimming");
		std::cin >> key;
		if (key == 0)
		{
			// Initialize serial port
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
				cap.read (img);
				int waitkey = cv::waitKey (20);
				if (waitkey == 49)
				{
					cv::destroyWindow ("Cam");
					break;
				}
				else if (waitkey == 48)
				{
					imgPre = preprocess (img);
					cv::imshow ("Preprocess", img);
					piece_results = gettarget (imgPre, colorranges);
					order (piece_results, target);
					log ("Prepare successfully !");
					drawresult (img, target);
					cv::imshow ("Target", img);
					cv::waitKey (2000);
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
			while (true)
			{
				int aim_type;
				log ("0. static aim");
				log ("1. dynamic aim");
				log ("2. exit aim")
				std::cin >> aim_type;
				// if (aim_type == 0)
				// {
				// 	aimming (cap, target, 5, laser_lower, laser_upper, fd);
				// }
				if (aim_type == 1)
				{
					int is_success;
					int n = 0;

					while (n < 5)
					{
						log ("Aimming Target " << n);
						is_success = daimming (fd, cap, target[n].bbox, laser_lower, laser_upper);
						if (is_success == 1)
						{
							log ("Aimming Target " << n << "successfully !");
						}
						else if (is_success == 0)
						{
							log ("Aimming Target Interrupted !");
							log ("return to reaimming...");
							break;
						}
						waitfor (cap);
						n++;

					}

					if (n > 5)
					{
						log ("Aimming Finished !");
					}

					// sned the end state to the MCU
					data end_aim;
					strcpy (end_aim.to_send, "end !");
					end_aim.end = '\t';
					write (fd, &end_aim, sizeof (end_aim));
					
				}
				else if (aim_type == 2)
				{
					break;
				}
				else
				{
					log ("Input Error");
				}

			}
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
