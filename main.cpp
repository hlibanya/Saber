#include "CppUTest/CommandLineTestRunner.h"
#include <iostream>
int main(int ac, char** av)
{
    CommandLineTestRunner::RunAllTests(ac, av);
    std::cin.get();
    return 0;
}