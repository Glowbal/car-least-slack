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
	virtual ~Machine();

	Machine& operator=(const Machine& base);
	bool operator==(const Machine& base) const;
	bool operator<(const Machine& base) const;

	unsigned long getID() const;
	void addTask(TaskPtr t);
	bool isFree(unsigned long time) const;
	unsigned long getFreeMoment() const;
    private:
	unsigned long ID;
	unsigned long time;

	std::vector<TaskPtr> scheduledTasks;
};

#endif /* MACHINE_HPP_ */
