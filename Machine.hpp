/*
 * Machine.hpp
 *
 *  Created on: 29 sep. 2014
 *      Author: Thomas Kooi
 */

#ifndef MACHINE_HPP_
#define MACHINE_HPP_
#include <vector>
class Task;
class Machine
{
    public:
	Machine(unsigned long id = 0);
	virtual ~Machine();

	Machine& operator=(const Machine& base);
	bool operator==(const Machine& base) const;
	bool operator<(const Machine& base) const;

	unsigned long getID() const;
	void addTask(Task& t);
	bool isFree(unsigned long time) const;

    private:
	unsigned long ID;
	unsigned long time;

	std::vector<Task> scheduledTasks;
};

#endif /* MACHINE_HPP_ */
