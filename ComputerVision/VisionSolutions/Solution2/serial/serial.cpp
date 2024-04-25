#include "serial.h"
#include <termios.h>
#include <unistd.h>

/**
 * @brief 初始化串口
 *
 * @param path 串口的文件路径
 * @return 返回串口文件描述符
 */
int SerialInit (const char* path)
{
	int fd;
	log ("----------------- Start Serial Port Control -----------------");
	fd = open (path, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		log ("Open Port Failed !");
	}
	else
	{
		log ("Open Port" << path << "Successfully !");
	}

	return fd;
}

/**
 * @brief 设置串口的参数
 *
 * @param fd 目标串口的文件描述符
 * @param buadrate 设置的波特率，要求为 @termios-baud.h 中的宏定义
 * @param datasize 要传输的数据位大小，要求为 @termios-c_cflag.h 中的宏定义
 *
 * @note `termios-baud.h` 和 `termios-c_cflag.h` 均包含于 `termios.h` 头文件中
 * @return 成功设置串口返回 1, 失败则返回 0
 */
int SerialSetting (int fd, int buadrate, int datasize)
{
	termios SPSettings;
	// get the original settings
	tcgetattr (fd, &SPSettings);

	// Setting the buad rate
	cfsetispeed (&SPSettings, buadrate);
	cfsetospeed (&SPSettings, buadrate);

	// Setting the parity to be closed
	SPSettings.c_cflag &= ~PARENB;

	// Setting the stop bit to be 1 bit
	SPSettings.c_cflag &= ~CSTOPB;

	// Setting the data bit to be 8 bits
	SPSettings.c_cflag &= ~CSIZE; // clear the size
	SPSettings.c_cflag |= datasize; // set to 8 bits

	// Starting the char receive
	SPSettings.c_cflag |= CREAD | CLOCAL;

	// Setting the flow control
	// close the hardware control
	SPSettings.c_cflag &= ~CRTSCTS;
	
	// close the software control
	// close the puase function when sending and receiving data
	// close the restart function when receive the start character
	SPSettings.c_iflag &= ~(IXON | IXOFF | IXANY);

	// close the process before data into the program
	// close the local echo and sign
	SPSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	// close the process before data being sent out
	SPSettings.c_oflag &= ~OPOST;

	if (tcsetattr (fd, TCSANOW, &SPSettings) != 0)
	{
		log ("Setting Attributes ERROR !");
		return 0;
	}
	else
	{
		log ("Setting Attribute Successfully");
		return 1;
	}
}

/**
 * @brief 用于发送目标数据
 *
 * @param fd 串口的文件描述符
 * @param to_send 要发送的数据
 * @return 发送的数据大小
 */
int senddata (int fd, std::string to_send)
{
	int write_byte = 0;
	// data d;
	// strcpy (d.to_send, to_send.c_str ());
	write_byte = write (fd, &to_send, 50);

	return write_byte;
}

/**
 * @brief 关闭串口
 *
 * @param fd 串口文件描述符
 */
void closeserial (int fd)
{
	close (fd);
}
