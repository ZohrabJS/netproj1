// netproj1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
#include "net-utils.h"

int main(int argc, char* argv[])
{
    if (argc == 10 || !_stricmp(argv[1], "server") )
    {
        std::cout << "UDP Server!\n";
        TinyUDPServer();
    }
    else
    {
        std::cout << "UDP Client!\n";
        TinyUDPClient();
    }
}
