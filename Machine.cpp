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
	ID(id)
{
}

Machine::Machine(const Machine& base) :
	ID(base.ID), scheduledTasks(base.scheduledTasks)
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
	scheduledTasks = base.scheduledTasks;
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
	if (!canFitTaskIn(t))
	{
	    unsigned long freeMoment = getFreeMoment();
	    std::cout << "Machine was occupied, so we schedule this later: " << t->getScheduleTime()
		    << " NEW: " << freeMoment << std::endl;
	    if (freeMoment <= t->getScheduleTime())
	    {
		std::cout << "ERROR GOING BACKWARDS IN TIME" << std::endl;
	    }
	    t->setScheduleTime(freeMoment);
	}
    }
    scheduledTasks.push_back(t);
}

bool Machine::canFitTaskIn(TaskPtr task) const
{
    for (unsigned int i = task->getScheduleTime();
	    i < (task->getScheduleTime() + task->getDuration()); ++i)
    {
	if (!isFree(i))
	{
	    return false;
	}
    }
    return true;
}

bool Machine::isFree(unsigned long time) const
{
    if (scheduledTasks.empty())
    {
	return true;
    }
    return ((scheduledTasks.back()->getScheduleTime() + scheduledTasks.back()->getDuration())
	    <= time);
}

unsigned long Machine::getFreeMoment() const
{
    if (!scheduledTasks.empty())
    {
	return scheduledTasks.back()->getScheduleTime() + scheduledTasks.back()->getDuration();
    }
    return 0;
}

void Machine::printSchedule() const {

    std::cout << "Printing for machine: " << std::endl;
    for (const TaskPtr t : scheduledTasks)
    {
	std::cout << "Task: " << t->getId() << " Time: "<< t->getScheduleTime() << std::endl;
    }
}
