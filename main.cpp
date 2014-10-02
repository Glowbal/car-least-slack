/*
 * main.cpp
 *
 *  Created on: 16 sep. 2014
 *      Author: Thomas Kooi, Michiel Buevink
 */

#include "JobShop.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    try
    {
	JobShop shop("test_input2.txt");
	shop.schedule();
	shop.printSchedule();
    }
    catch (std::exception& e)
    {
	std::cout << "Error: " << e.what() << std::endl;
    }
    catch (...)
    {
	std::cout << "Caught an unknown exception" << std::endl;
    }
    return 0;
}

