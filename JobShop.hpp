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

	/**
	 * Schedules all jobs using the Least Slack Algorithm.
	 *
	 */
	void schedule();

	/**
	 * Goes through the Jobs and prints begin and end times.
	 */
	void printSchedule();

	/**
	 * Returns machine with given ID.
	 * @Param n The ID from machine.
	 *
	 * @Return Pointer to machine with ID.
	 *
	 * @Throws std::out_of_range if machine does not exist.
	 */
	Machine* getMachineAt(unsigned long n);

    private:
	Jobs jobs;
	std::vector<Machine> machines;
	unsigned long numberOfJobs;
	unsigned long numberOfMachines;
	unsigned long currentTime;

	Jobs::iterator getLeastSlackJob();
	bool hasUnscheduledTasks();
};

#endif /* JOBSHOP_HPP_ */
