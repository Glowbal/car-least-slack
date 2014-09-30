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
}

Machine::~Machine()
{
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

void Machine::addTask(TaskPtr t)
{
    if (!scheduledTasks.empty())
    {
	if (!isFree(t->getScheduleTime()))
	{
	    t->setScheduleTime(getFreeMoment());
	}
    }
    scheduledTasks.push_back(t);
}

bool Machine::isFree(unsigned long time) const
{
    if (scheduledTasks.empty())
    {
	return true;
    }
    return ((scheduledTasks.back()->getScheduleTime() + scheduledTasks.back()->getDuration()) <= time);
}

unsigned long Machine::getFreeMoment() const
{
    if (!scheduledTasks.empty())
    {
	return scheduledTasks.back()->getScheduleTime() + scheduledTasks.back()->getDuration();
    }
    return 0;
}
