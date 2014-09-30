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
	ID(0), latestTaskID(0), shop(nullptr), positionCounter(0)
{

}

Job::~Job()
{
}

Job::Job(unsigned long id, const std::string& jobLine, JobShop* baseShop) :
	ID(id), latestTaskID(0), shop(baseShop), positionCounter(0)
{
    unsigned short machineNumber = 0;
    unsigned short time = 0;
    try
    {
	boost::regex regex("(\\d+\\s+\\d+)+", boost::regex_constants::icase);
	boost::smatch base_match;
	boost::sregex_token_iterator iter(jobLine.begin(), jobLine.end(), regex, 0);
	boost::sregex_token_iterator end;

	for (; iter != end; ++iter)
	{
	    std::istringstream iss(*iter);
	    iss >> machineNumber >> time;
	    Task newTask(latestTaskID, machineNumber, time);
	    ++latestTaskID;
	    unscheduledTasks.push_back(newTask);
	    std::cout << machineNumber << " - " << time << " | ";
	}
	std::cout << std::endl;

    }
    catch (std::exception& e)
    {
	std::cout << e.what() << std::endl;
    }
}

Job& Job::operator=(const Job& base)
{
    if (this != &base)
    {
	ID = base.ID;
	latestTaskID = base.latestTaskID;
	unscheduledTasks = base.unscheduledTasks;
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
    return ID < base.ID;
}

unsigned long Job::getId() const
{
    return ID;
}

unsigned long Job::getDeadline()
{
    unsigned long moment = 0;
    if (positionCounter > 0)
    {
	moment += unscheduledTasks.at(positionCounter - 1).getDuration();
	moment += unscheduledTasks.at(positionCounter - 1).getScheduleTime();
    }
    for (unsigned long i = positionCounter; i < unscheduledTasks.size(); ++i)
    {
	unsigned long machineN = unscheduledTasks.at(i).getMachineN();
	if (shop->getMachineAt(machineN)->isFree(moment))
	{
	    if (unscheduledTasks.at(i).getScheduleTime() > 0)
	    {
		moment = unscheduledTasks.at(i).getScheduleTime();
	    }
	    moment += unscheduledTasks.at(i).getDuration();
	}
	else
	{
	    if (shop->getMachineAt(machineN)->getFreeMoment() > moment)
	    {
		moment = shop->getMachineAt(machineN)->getFreeMoment();
	    }
	    moment += unscheduledTasks.at(i).getDuration();
	}
    }
    return moment;
}

bool Job::hasUnscheduledTasks() const
{
    return (unscheduledTasks.back().getScheduleTime() == 0);
}

unsigned long Job::getNextTaskMachineN() const
{
    if (hasUnscheduledTasks())
    {
	return unscheduledTasks.at(positionCounter).getMachineN();
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
	    Task& t = unscheduledTasks.at(positionCounter);
	    unsigned long moment = 0;
	    if (positionCounter > 0)
	    {
		moment = (unscheduledTasks.at(positionCounter - 1).getDuration()
			+ unscheduledTasks.at(positionCounter - 1).getScheduleTime());
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
