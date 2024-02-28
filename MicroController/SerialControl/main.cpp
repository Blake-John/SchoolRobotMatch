// #include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
// #include <errno.h>
#include <iostream>
// #include <cstring>

#define log(x) std::cout << x << std::endl;

int main ()
{
    int fd; // File Descriptor

    log ("-----------------------Start Serial Port Write------------------------");

    fd = open ("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1)
    {
        log ("Open File Failed !");
    }
    else
    {
        log ("Open ttyUSB0 Successfully !");
    }

    termios SerialPortSettings;

    tcgetattr (fd, &SerialPortSettings);

    // 设置 波特率
    cfsetispeed (&SerialPortSettings, B9600);
    cfsetospeed (&SerialPortSettings, B9600);

    // 设置校验位
    SerialPortSettings.c_cflag &= ~PARENB;

    // 设置停止位 = 1
    SerialPortSettings.c_cflag &= ~CSTOPB;
    SerialPortSettings.c_cflag &= ~CSIZE;

    // 设置数据位 = 8
    SerialPortSettings.c_cflag |= CS8;

    SerialPortSettings.c_cflag &= ~CRTSCTS;
    SerialPortSettings.c_cflag |= CREAD | CLOCAL;

    // 设置流控
    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);

    // 设置操作模式
    SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    SerialPortSettings.c_oflag &= ~OPOST;

    if (tcsetattr (fd, TCSANOW, &SerialPortSettings) != 0)
    {
        log ("Setting Attributes ERROR !");
    }
    else
    {
        log ("Setting Attributes Successfully !");
        log ("BaudRate = 9600\nStopBits = 1\nParity = None");
    }
    // char* buffer;
    // int write_byte = 0;
    // char buffer[] = "ABCDEFGHJIKL";
    // char buffer[10];
    struct data
    {
        char head;
        char data[100];
        char end;
    };
    
    // uint8_t* bufferpt = &buffer;
    int write_byte = 0;

    // // buffer >> fd;
    // // log (buffer << " is send !");
    // // log ("The size of the data : " << sizeof (buffer));

    // write_byte = write (fd, bufferpt, sizeof (buffer));
    // // write_byte = write (fd, "FASDF", 8);
    // log (buffer << " is written to ttyUSB0");
    // // log ("A is send !");
    // log ("The size of the data : " << write_byte);
    // log ("-------------------------------------------");

    // while (std::cin >> buffer)
    // {
    //     // write_byte = write (fd, &buffer, sizeof (buffer));
    //     std::write ()
    //     log (buffer << " is written to ttyUSB0");
    //     log ("The size of the data : " << write_byte);
    //     log ("-------------------------------------------");
    // }
    
    // while (1)
    // {
    //     char* buffer[1024];
    //     int read_byte;
    //     read_byte = read (fd, buffer, sizeof (buffer));
    //     // if (strcmp ((const char*)buffer, "") != 0)
    //     // {
    //     //     std::cout << buffer << std::endl;
    //     // }
    //     std::cout << *buffer << std::endl;
        
    // }
    data Data;
    Data.head = '@';
    Data.end = '\n';

    while (1)
    {
        std::cin >> Data.data;
        write_byte = write (fd, &Data, sizeof (Data));
        log (Data.data << " is written to ttyUSB0");
        log ("The size of the data : " << write_byte);
        log ("-------------------------------------------");

    }
    
    

    close (fd);
    
}
