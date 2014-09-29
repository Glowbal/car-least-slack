/*
 * JobShop.cpp
 *
 *  Created on: 16 sep. 2014
 *      Author: Thomas Kooi
 */

#include "JobShop.hpp"
#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <exception>
#include <climits>

JobShop::JobShop() :
	numberOfJobs(0), numberOfMachines(0), currentTime(0)
{
}

JobShop::~JobShop()
{
}

JobShop::JobShop(const std::string& jobFileName) :
	numberOfJobs(0), numberOfMachines(0), currentTime(0)
{
    std::ifstream file(jobFileName);
    std::string line;
    if (file.is_open())
    {
	// Getting the first line for amount of jobs and machines
	if (std::getline(file, line))
	{
	    std::istringstream iss(line);
	    iss >> numberOfJobs >> numberOfMachines;
	    for (unsigned long i = 0; i < numberOfMachines; i++)
	    {
		machines.push_back(Machine(i));
	    }
	}
	unsigned long id = 0;
	while (std::getline(file, line))
	{
	    try
	    {
		Job newJob(id, line, this);
		jobs.push_back(newJob);
		++id;
	    }
	    catch (std::exception& e)
	    {
		std::cout << e.what() << line << std::endl;
	    }
	}
	file.close();
    }
}

Job* JobShop::getLeastSlackJob()
{
    unsigned long latestdeadline = 0;
    Job* latestJob = nullptr;
    for (Job& j : jobs)
    {
	if (latestdeadline <= j.getDeadline())
	{
	    latestdeadline = j.getDeadline();
	    latestJob = &j;
	}
    }
    return latestJob;
}

/*
 1) bereken leastSlack
 2) pak eerste taak van job met leastslack. Kijk of machineN vrij is.
 JA:	Voeg tot aan schedule lijst met: start time (currentTime)

 NEE: Pak eenna least slack, repeat.

 3) voor elke vrije machine:
 kijk of eerste taak van een job op die machine hoort.
 JA: voeg tot aan schedule lijst met: start time (currentTime)

 NEE: niks

 terug naar 1).
 *
 */
void JobShop::schedule()
{

    while (hasUnscheduledTasks())
    {
	// std::sort(jobs.begin(), jobs.end());
	Job* latestJob = getLeastSlackJob();
	if (latestJob != nullptr)
	{
	    latestJob->schedule();
	}
    }

}

bool JobShop::hasUnscheduledTasks()
{
    for (const Job& j : jobs)
    {
	if (j.hasUnscheduledTasks())
	{
	    return true;
	}
    }
    return false;
}

bool JobShop::machineFree(unsigned long machineNumber) const
{
    return machines.at(machineNumber).isFree(currentTime);
}

Machine* JobShop::getMachineAt(unsigned long n)
{
    if (n > machines.size()) {
	return &machines.at(0);
    }
    return &machines.at(n);
}

void JobShop::printSchedule()
{
    std::cout << "---------------" << std::endl;
    std::cout << "Schedule:\n";
    unsigned long c = 0;
    for (const Job& j : jobs)
    {
	std::cout << c << " " << j.unscheduledTasks.at(0).getScheduleTime() << " "
		<< j.unscheduledTasks.back().getScheduleTime() + j.unscheduledTasks.back().getDuration()
		<< std::endl;
	c++;
    }
}

