#include "serial.h"
#include <iterator>
#include <termios.h>
#include <unistd.h>

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

int SerialSetting (int fd, int buadrate, int datasize)
{
	termios SPSettings;
	tcgetattr (fd, &SPSettings);

	// Setting the buad rate
	cfsetispeed (&SPSettings, B9600);
	cfsetospeed (&SPSettings, B9600);

	// Setting the parity to be closed
	SPSettings.c_cflag &= ~PARENB;

	// Setting the stop bit to be 1 bit
	SPSettings.c_cflag &= ~CSTOPB;
	SPSettings.c_cflag &= ~CSIZE;

	// Setting the data bit to be 8 bits
	SPSettings.c_cflag |= CS8;

	SPSettings.c_cflag &= ~CRTSCTS;
	SPSettings.c_cflag |= CREAD | CLOCAL;
	
	// Setting the flow control
	SPSettings.c_iflag &= ~(IXON | IXOFF | IXANY);

	// Setting the operate mode
	SPSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	SPSettings.c_oflag &= ~OPOST;

	if (tcsetattr (fd, TCSANOW, &SPSettings) != 0)
	{
		log ("Setting Attributes ERROR !");
		return 0;
	}
	else
	{
		log ("Setting Attribute Successfully");
		return 0;
	}
}

int senddata (int fd, const char* to_send)
{
	int write_byte = 0;
	data d;
	d.to_send = to_send;
	write_byte = write (fd, &d, sizeof (d));

	return write_byte;
}

void closeserial (int fd)
{
	close (fd);
}
