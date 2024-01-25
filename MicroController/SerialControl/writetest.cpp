#include <iostream>
#include <fstream>

int main ()
{
    std::fstream file;

    file.open ("../test.txt", std::ios_base::app | std::ios_base::in);
    std::string buffer;
    char* myword = "ABC";

    if (file.is_open ())
    {
        file << "Hello File !" << std::endl;
        
        // file.write (myword, sizeof (myword) - 1);
        
        file.close ();
    }
    else
    {
        std::cout << "Open File Failed !" << std::endl;
    }
    

    return 0;
}