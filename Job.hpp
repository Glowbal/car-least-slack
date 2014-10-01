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
	virtual ~Job();
	Job(unsigned long id, const std::string& jobLine, JobShop* baseShop = nullptr);
	Job(const Job& j);

	Job& operator=(const Job& base);
	bool operator==(const Job& base) const;
	bool operator<(const Job& base) const;

	/**
	 *
	 * @Return ID of this job.
	 */
	unsigned long getId() const;

	/**
	 * Gets the deadline of job based upon:
	 *  Total duration of unscheduled tasks + moment last scheduled task is finished.
	 * @Return Deadline for task.
	 */
	unsigned long getDeadline() const;

	/**
	 * @Return true while last task is unscheduled.
	 */
	bool hasUnscheduledTasks() const;

	/**
	 * Checks if this job is currently scheduled on the given machine ID at the given time.
	 * @Param num the ID of the machine to check.
	 * @Param currentTime The time moment on which there will be checked.
	 *
	 * @Return True if is currently scheduled on given machine.
	 */
	bool isScheduledOnMachine(unsigned short num, unsigned long currentTime) const;

	/**
	 * @Return The next unscheduled tasks machine ID.
	 */
	unsigned long getNextTaskMachineN() const;

	/**
	 * Schedules the next task in line on the given machine.
	 * Once the job has nothing more to schedule, this will do nothing.
	 */
	void schedule();

	/**
	 * Adds a new tasks for this job and places it in the back of the line.
	 * @Param machineNumber The ID of the machine this task should be executed on.
	 * @Param time The time it takes for this task to complete; duration.
	 *
	 */
	void addTask(unsigned long machineNumber, unsigned long time);

	/**
	 * The task list. A vector with std::shared_ptrs to Tasks.
	 */
	TaskPtr_vector taskList;

    private:
	unsigned long ID;
	JobShop* shop;
	unsigned long positionCounter;
};

typedef std::vector<Job> Jobs;

#endif /* JOB_HPP_ */
