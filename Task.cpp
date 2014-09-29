/*
 * Task.cpp
 *
 *  Created on: 16 sep. 2014
 *      Author: Thomas Kooi
 */

#include "Task.hpp"
#include <iostream>
#include <algorithm>

Task::~Task()
{
    // TODO Auto-generated destructor stub
}

Task::Task(unsigned long theId, unsigned long machineNumber, unsigned short timeTask) :
	id(theId), machineN(machineNumber), duration(timeTask), scheduleTime(
		0)
{
    std::cout << "Machine number: " << machineN << " duration: " << duration << std::endl;
}
Task::Task(const Task& t) :
	id(t.id), machineN(t.machineN), duration(t.duration), scheduleTime(t.scheduleTime)
{
}

Task& Task::operator=(const Task& base)
{
    if (this != &base)
    {
	id = base.id;
	machineN = base.machineN;
	duration = base.duration;
	scheduleTime = base.scheduleTime;
    }
    return *this;
}

bool Task::operator==(const Task& base) const
{
    return id == base.id;
}

bool Task::operator<(const Task& base) const
{
    return id < base.id;
}

unsigned short Task::getDuration() const
{
    return duration;
}

unsigned long Task::getId() const
{
    return id;
}

unsigned long Task::getMachineN() const
{
    return machineN;
}

unsigned long Task::getScheduleTime() const
{
    return scheduleTime;
}

void Task::setScheduleTime(unsigned long scheduleTime)
{
    this->scheduleTime = scheduleTime;
}

void Task::schedule() {
   // machineN.addTask(this);
}
