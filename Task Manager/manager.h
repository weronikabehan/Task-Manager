#ifndef MANAGER_H
#define MANAGER_H

#include "task.h"
#include <vector>
#include <memory>

class Manager {
private:
	std::vector<std::unique_ptr<Task>> vecTask;
public:
	Manager() = default;
	std::vector<std::unique_ptr<Task>>& getVec() { return vecTask; }

	void addTask(std::string n) { vecTask.emplace_back(std::make_unique<Task>(n)); }
	void deleteTask(int index) { vecTask.erase(vecTask.begin() + index); }
	
	void changeNameORDesc(int index, int what, const std::string& name);
	void changePriority(int index, int what);
	void changeCategory(int index, const std::string& category);
	void changeDone(int index);

	void stringToTP(int day, int month, int year, int hour, int minute);
};

#endif