#include "serial.h"

int main ()
{
	int fd, key;
	fd = SerialInit ("/dev/ttyUSB0");
	key = SerialSetting (fd, B9600, CS8);

	if (key == 1)
	{
		
	}

	return 0;
}
