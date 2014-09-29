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
    // TODO Auto-generated constructor stub

}

Job::~Job()
{
    // TODO Auto-generated destructor stub
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
// shop->getMachineAt(machineNumber)
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

    for (unsigned long i = positionCounter; i < unscheduledTasks.size(); i++)
    {
	moment += unscheduledTasks.at(i).getDuration();
    }

    return moment;
}

bool Job::hasUnscheduledTasks() const
{
    return (positionCounter != unscheduledTasks.size());
}

/*bool Job::isScheduledOnMachine(unsigned short num, unsigned long currentTime) const
 {
 if (!scheduledTasks.empty())
 {
 const Task& t = scheduledTasks.back();
 if ((t.getScheduleTime() + t.getDuration()) >= currentTime
 && t.getScheduleTime() <= currentTime)
 {
 return (t.getMachineN().getID() == num);
 }
 }
 return false;
 }*/

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
	//std::sort(unscheduledTasks.begin(), unscheduledTasks.end());
	if (hasUnscheduledTasks())
	{
	    std::cout << "----------------------" << std::endl;
	    Task& t = unscheduledTasks.at(positionCounter);
	    unsigned long moment = 0;
	    for (unsigned long i = 0; i < positionCounter; i++)
	    {
		std::cout << unscheduledTasks.at(i).getDuration() << " " << unscheduledTasks.at(i).getScheduleTime() << std::endl;
		moment = (unscheduledTasks.at(i).getDuration()
			+ unscheduledTasks.at(i).getScheduleTime());
	    }
	    t.setScheduleTime(moment);
	    std::cout << "original scheduletime: " << t.getScheduleTime() << std::endl;
	    // t.schedule();
	    if (shop == nullptr) {
		std::cout << "It's a nullptr \n";
	    } else {
		shop->getMachineAt(t.getMachineN())->addTask(t);
	    }

	    //scheduledTasks.push_back(t);
	    std::cout << "Scheduled task: " << ID << "." << t.getId() << " at time: "
		    << t.getScheduleTime() << " duration:" << t.getDuration() << " machineN:"
		    << t.getMachineN() << std::endl;
	    positionCounter++;
	    //unscheduledTasks.erase(unscheduledTasks.begin());
	}

}
