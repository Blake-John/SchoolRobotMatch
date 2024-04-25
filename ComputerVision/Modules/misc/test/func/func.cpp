#include "func.h"
#include "serial.h"
#include <unistd.h>

void mainloop (int fd)
{
	while (true)
	{
		log ("Please choose the function : ");
		log ("0. Send Data");
		log ("1. Read Data");
		int choice;
		std::cin >> choice;
		if (choice == 0)
		{
			log ("Please input the data to send : ");
			char* data;
			std::cin >> data;
			senddata (fd, data);
		}
		else if (choice == 1)
		{
			char* buf;
			read (fd, buf, 20);
			log (buf);
		}
	}
}
