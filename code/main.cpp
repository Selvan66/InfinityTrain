#include <iostream>
#include <exception>

#include "App/Application.h"

int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}