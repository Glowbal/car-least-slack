/*
 * JobShop.hpp
 *
 *  Created on: 16 sep. 2014
 *      Author: Thomas Kooi
 */
#include <vector>
#include <string>
#include "Job.hpp"

#ifndef JOBSHOP_HPP_
#define JOBSHOP_HPP_

class JobShop
{
    public:
	JobShop();
	virtual ~JobShop();
	JobShop(const std::string& jobFileName);

	void schedule();
	void printSchedule();
	Machine* getMachineAt(unsigned long n);

    private:
	std::vector<Job> jobs;
	std::vector<Machine> machines;
	unsigned long numberOfJobs;
	unsigned long numberOfMachines;
	unsigned long currentTime;

	 Job* getLeastSlackJob();
	 bool hasUnscheduledTasks();
	 bool machineFree(unsigned long machineNumber) const;


};

#endif /* JOBSHOP_HPP_ */
