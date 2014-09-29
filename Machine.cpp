/*
 * Machine.cpp
 *
 *  Created on: 29 sep. 2014
 *      Author: Thomas Kooi
 */

#include "Machine.hpp"
#include "Task.hpp"
#include <iostream>

Machine::Machine(unsigned long id) :
	ID(id), time(0)
{
    // TODO Auto-generated constructor stub

}

Machine::~Machine()
{
    // TODO Auto-generated destructor stub
}

unsigned long Machine::getID() const
{
    return ID;
}
Machine& Machine::operator=(const Machine& base)
{
    if (this != &base)
    {
	ID = base.ID;
    }
    return *this;
}

bool Machine::operator==(const Machine& base) const
{
    return ID == base.ID;
}

bool Machine::operator<(const Machine& base) const
{
    return ID < base.ID;
}

void Machine::addTask(Task& t)
{

    if (!scheduledTasks.empty())
    {
	unsigned long taskTime = t.getScheduleTime();
	unsigned long lastcompleted = scheduledTasks.back().getScheduleTime()
		+ scheduledTasks.back().getDuration();
	unsigned long time = taskTime;
	if (taskTime < lastcompleted)
	{
	    time = lastcompleted;
	}
	t.setScheduleTime(time);
    }
    scheduledTasks.push_back(t);
}

bool Machine::isFree(unsigned long time) const
{
    if (scheduledTasks.empty())
    {
	return true;
    }
    else
    {
	return ((scheduledTasks.back().getScheduleTime() + scheduledTasks.back().getDuration())
		<= time);
    }
    return false;

}
