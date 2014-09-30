/*
 * Task.hpp
 *
 *  Created on: 16 sep. 2014
 *      Author: Thomas Kooi
 */

#ifndef TASK_HPP_
#define TASK_HPP_
#include <memory>
#include "Machine.hpp"
typedef std::shared_ptr<Task> TaskPtr;

class Task
{
    public:

	virtual ~Task();
	Task(unsigned long theId, unsigned long machineNumber, unsigned short timeTask=0);
	Task(const Task& t);

	Task& operator=(const Task& base);
	bool operator==(const Task& base) const;
	bool operator<(const Task& base) const;

	unsigned short getDuration() const;
	unsigned long getId() const;
	unsigned long getMachineN() const;
	unsigned long getScheduleTime() const;
	void setScheduleTime(unsigned long setTime);
	void schedule();

    private:
	unsigned long id;
	unsigned long machineN;
	unsigned short duration;
	unsigned long scheduleTime;

};

#endif /* TASK_HPP_ */
