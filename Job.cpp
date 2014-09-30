/*
 * Job.cpp
 *
 *  Created on: 16 sep. 2014
 *      Author: Thomas Kooi
 */
#include <sstream>
#include <iostream>
#include "Job.hpp"
#include <climits>
#include <boost/regex.hpp>
#include "JobShop.hpp"

Job::Job() :
	ID(0), shop(nullptr), positionCounter(0)
{
}

Job::~Job()
{
}

void Job::addTask(unsigned long machineNumber, unsigned long time)
{
    taskList.push_back(Task(taskList.size(), machineNumber, time));
}

Job::Job(unsigned long id, const std::string& jobLine, JobShop* baseShop) :
	ID(id), shop(baseShop), positionCounter(0)
{
    try
    {
	unsigned short machineNumber = 0;
	unsigned short time = 0;
	boost::regex regex("(\\d+\\s+\\d+)+", boost::regex_constants::icase);
	boost::smatch base_match;
	boost::sregex_token_iterator beginIterator(jobLine.begin(), jobLine.end(), regex, 0);
	boost::sregex_token_iterator endIterator;

	for (; beginIterator != endIterator; ++beginIterator)
	{
	    std::istringstream inputSStream(*beginIterator);
	    inputSStream >> machineNumber >> time;
	    addTask(machineNumber, time);
	}
	std::cout << std::endl;
    }
    catch (std::exception& e)
    {
	std::cout << e.what() << std::endl;
	throw e;
    }
}

Job& Job::operator=(const Job& base)
{
    if (this != &base)
    {
	ID = base.ID;
	taskList = base.taskList;
	scheduledTasks = base.scheduledTasks;
	positionCounter = base.positionCounter;
    }
    return *this;
}

bool Job::operator==(const Job& base) const
{
    return ID == base.ID;
}

bool Job::operator<(const Job& base) const
{
    return (getDeadline() < base.getDeadline());
}

unsigned long Job::getId() const
{
    return ID;
}

unsigned long Job::getDeadline() const
{
    unsigned long moment = 0;
    if (positionCounter > 0)
    {
	moment += taskList.at(positionCounter - 1).getDuration();
	moment += taskList.at(positionCounter - 1).getScheduleTime();
    }
    for (unsigned long i = positionCounter; i < taskList.size(); ++i)
    {
	unsigned long machineN = taskList.at(i).getMachineN();
	if (shop->getMachineAt(machineN)->isFree(moment))
	{
	    if (taskList.at(i).getScheduleTime() > 0)
	    {
		moment = taskList.at(i).getScheduleTime();
	    }
	    moment += taskList.at(i).getDuration();
	}
	else
	{
	    if (shop->getMachineAt(machineN)->getFreeMoment() > moment)
	    {
		moment = shop->getMachineAt(machineN)->getFreeMoment();
	    }
	    moment += taskList.at(i).getDuration();
	}
    }
    return moment;
}

bool Job::hasUnscheduledTasks() const
{
    return (taskList.back().getScheduleTime() == 0);
}

unsigned long Job::getNextTaskMachineN() const
{
    if (hasUnscheduledTasks())
    {
	return taskList.at(positionCounter).getMachineN();
    }
    return 0;
}

void Job::schedule()
{
    try
    {
	if (hasUnscheduledTasks())
	{
	    std::cout << "----------------------" << std::endl;
	    Task& t = taskList.at(positionCounter);
	    unsigned long moment = 0;
	    if (positionCounter > 0)
	    {
		moment = (taskList.at(positionCounter - 1).getDuration()
			+ taskList.at(positionCounter - 1).getScheduleTime());
	    }
	    t.setScheduleTime(moment);
	    shop->getMachineAt(t.getMachineN())->addTask(t);

	    std::cout << "Scheduled task: " << ID << "." << t.getId() << " at time: "
		    << t.getScheduleTime() << " duration:" << t.getDuration() << " machineN:"
		    << t.getMachineN() << " Deadline of " << getDeadline() << std::endl;
	    positionCounter++;
	}
    }
    catch (std::exception& e)
    {
	std::cout << e.what() << std::endl;
	throw e;
    }
}
