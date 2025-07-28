#ifndef MANAGER_H
#define MANAGER_H

#include "task.h"
#include <vector>
#include <memory>

class Manager {
private:
	std::vector<std::unique_ptr<Task>> vecTask;
public:
	std::vector<std::unique_ptr<Task>> getVec() const { return vecTask; }

	void addTask(std::string n) { vecTask.emplace_back(std::make_unique<Task>(n)); }
	void deleteTask(int index);
};

#endif