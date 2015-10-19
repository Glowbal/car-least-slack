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
    try
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
		        for (unsigned long machineID = 0; machineID < numberOfMachines; ++machineID)
		        {
		            machines.push_back(Machine(machineID));
		        }
		        }
		        while (std::getline(file, line))
		        {
		        Job newJob(jobs.size(), line, this);
		        jobs.push_back(newJob);
		        }
		        file.close();
		    }
    }
    catch (std::exception& e)
    {
		    std::cout << e.what() << std::endl;
		    throw e;
    }
}

Jobs::iterator JobShop::getLeastSlackJob()
{
    unsigned long latestdeadline = 0;
    Jobs::iterator highest;
    for (Jobs::iterator it = jobs.begin(); it != jobs.end(); ++it)
    {
		    const Job& compareJob = (*it);
		    if (compareJob.hasUnscheduledTasks())
		    {
		        // compareJob.isFree(currentMoment);
		        unsigned long deadline = compareJob.getDeadline2();
		        if (latestdeadline < deadline)
		        {
				        latestdeadline = deadline;
				        highest = it;
		        }
		    }
    }
    return highest;
}

void JobShop::schedule()
{
    while (hasUnscheduledTasks())
    {
		    Jobs::iterator leastSlackJob = getLeastSlackJob();
		    (*leastSlackJob).schedule();
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

Machine* JobShop::getMachineAt(unsigned long n)
{
    if (n > machines.size())
    {
    		throw std::out_of_range("Trying to retrieve a machine but machine ID is to high");
    }
    return &machines.at(n);
}

void JobShop::printSchedule()
{
    unsigned long c = 0;
    for (const Job& j : jobs)
    {
		    std::cout << c << " " << j.taskList.front()->getScheduleTime() << " "
		        << j.taskList.back()->getScheduleTime() + j.taskList.back()->getDuration()
		        << std::endl;
		    ++c;
    }
}

void JobShop::printScheduleMachine(unsigned long machineId) const
{
    machines.at(machineId).printSchedule();
}
