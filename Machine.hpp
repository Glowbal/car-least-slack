/*
 * Machine.hpp
 *
 *  Created on: 29 sep. 2014
 *      Author: Thomas Kooi
 */

#ifndef MACHINE_HPP_
#define MACHINE_HPP_
#include <vector>
#include <memory>
class Task;
typedef std::shared_ptr<Task> TaskPtr;

class Machine
{
    public:
	Machine(unsigned long id = 0);
	Machine(const Machine& base);
	virtual ~Machine();

	Machine& operator=(const Machine& base);
	bool operator==(const Machine& base) const;
	bool operator<(const Machine& base) const;

	/**
	 * Returns the machine ID.
	 */
	unsigned long getID() const;

	/**
	 * Add a task to the scheduled list.
	 * Sets the task scheduled time to first free moment
	 * if scheduled time is lower as the machines first free moment.
	 *
	 * @param t The new task that will be added to the scheduled list.
	 */
	void addTask(TaskPtr t);

	/**
	 * Checks if the machine is free at given moment.
	 * @param time Moment in time to check if machine is free.
	 *
	 * @Return True if machine is free at moment.
	 */
	bool isFree(unsigned long time) const;

	/**
	 * Get the first moment the machine has no tasks scheduled anymore.
	 * @Return Moment after the last scheduled task is finished.
	 */
	unsigned long getFreeMoment() const;

	/**
	 * Checks if the task can be fit in with its current scheduled starting time.
	 * @return true if task can be scheduled at its current scheduled time.
	 */
	bool canFitTaskIn(TaskPtr t) const;

	/**
	 *
	 */
	void printSchedule() const;

    private:
	unsigned long ID;
	std::vector<TaskPtr> scheduledTasks;
};

#endif /* MACHINE_HPP_ */
