#include "serial.h"
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

int senddata (int fd, char* to_send)
{
	int write_byte = 0;
	data d;
	d.to_send = to_send;
	write_byte = write (fd, &d, 20);

	return write_byte;
}

void closeserial (int fd)
{
	close (fd);
}
