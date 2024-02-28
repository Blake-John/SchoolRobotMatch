#pragma once

#include <fcntl.h>
#include <iterator>
#include <termios.h>
#include <iostream>
#include <unistd.h>

#define log(x) std::cout << x << std::endl;

struct data
{
	char head = '@';
	const char* to_send;
	char end = '\n';
};

int SerialInit (const char* path);
int SerialSetting (int fd, int baudrate, int datasize);
int senddata (int fd, const char* to_send);
void closeserial (int fd);
