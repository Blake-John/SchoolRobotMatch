#pragma once

#include <fcntl.h>
#include <iterator>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

#define log(x) std::cout << x << std::endl;

struct data
{
	char head = '@';
	char to_send[50];
	char end = '\n';
};

int SerialInit (const char* path);
int SerialSetting (int fd, int baudrate, int datasize);
int senddata (int fd, std::string to_send);
void closeserial (int fd);

