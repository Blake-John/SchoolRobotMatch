#include <fcntl.h>
#include <iterator>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

int main ()
{
    int fd;
    // fd = open ("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    fd = open ("/dev/ttyUSB0", O_RDWR);
    if (fd == -1)
    {
        std::cout << "Failed !" << std::endl;
    }
    else
    {
        std::cout << "Succeed !" << std::endl;
    }
    const char* to_send = "@RE\n";
    // for (int i = 0; i < 4; i++)
    // {
    //     write(fd, to_send+i, 1);
    // }
    // write (fd, to_send, sizeof (to_send));
    struct datasent
    {
        char head = '@';
        char datap[10];
        char end = '\n';
    };
    datasent tosend;
    tosend.datap[0] = 'X';
    tosend.datap[1] = 'Y';

    write (fd, &tosend, sizeof (tosend));
    
    

    
}