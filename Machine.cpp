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
	    t->setScheduleTime(getFreeMoment());
	}
    }
    scheduledTasks.push_back(t);
}

bool Machine::canFitTaskIn(TaskPtr task) const
{
    unsigned long finishedAt = task->getScheduleTime() + task->getDuration();
    unsigned long scheduledAt = task->getScheduleTime();

    if (isFree(scheduledAt))
    {
	return true;
    }

    for (TaskPtr t : scheduledTasks)
    {
	unsigned long compareTaskFinishedAt = t->getScheduleTime() + t->getDuration();
	unsigned long compareTaskScheduledAt = t->getScheduleTime();

	if (scheduledAt >= compareTaskScheduledAt && scheduledAt <= compareTaskFinishedAt)
	{
	    return false;
	}
	else if (finishedAt >= compareTaskScheduledAt && finishedAt <= compareTaskFinishedAt)
	{
	    return false;
	}
	else if (scheduledAt < compareTaskScheduledAt && finishedAt > compareTaskFinishedAt)
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
    return ((scheduledTasks.back()->getScheduleTime() + scheduledTasks.back()->getDuration()) < time);
}

unsigned long Machine::getFreeMoment() const
{
    if (!scheduledTasks.empty())
    {
	return scheduledTasks.back()->getScheduleTime() + scheduledTasks.back()->getDuration();
    }
    return 0;
}

void Machine::printSchedule() const
{

    std::cout << "Printing for machine: " << std::endl;
    for (const TaskPtr t : scheduledTasks)
    {
	std::cout << "Task: " << t->getId() << " Time: " << t->getScheduleTime() << std::endl;
    }
}
