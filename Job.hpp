/*
 * Job.hpp
 *
 *  Created on: 16 sep. 2014
 *      Author: Thomas Kooi
 */

#ifndef JOB_HPP_
#define JOB_HPP_

#include <vector>
#include <string>
#include "Task.hpp"
class JobShop;

class Job
{
    public:
	Job();
	virtual ~Job();
	Job(unsigned long id, const std::string& jobLine, JobShop* baseShop = nullptr);

	Job& operator=(const Job& base);
	bool operator==(const Job& base) const;
	bool operator<(const Job& base) const;

	unsigned long getId() const;
	std::vector<Task> taskList;
	std::vector<Task> scheduledTasks;
	unsigned long getDeadline() const;
	bool hasUnscheduledTasks() const;
	bool isScheduledOnMachine(unsigned short num, unsigned long currentTime) const;
	unsigned long getNextTaskMachineN() const;
	void schedule();
	void addTask(unsigned long machineNumber, unsigned long time);

    private:
	unsigned long ID;
	JobShop* shop;
	unsigned long positionCounter;
};

#endif /* JOB_HPP_ */
