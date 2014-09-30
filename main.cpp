/*
 * main.cpp
 *
 *  Created on: 16 sep. 2014
 *      Author: Thomas Kooi, Michiel Buevink
 */
#include "JobShop.hpp"
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    JobShop shop("test.txt");
    shop.schedule();
    shop.printSchedule();
    return 0;
}

