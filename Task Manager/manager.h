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
	
	void changeNameORDesc(int index, int what, const std::string& name) {
		(what == 1) ? getVec().at(index)->setName(name) : getVec().at(index)->setDescription(name);
	}
	void changePriority(int index, int what) {
		switch (what) {
		case 1: getVec().at(index)->setPriority(prio::ASAP); break;
		case 2: getVec().at(index)->setPriority(prio::Later); break;
		case 3: getVec().at(index)->setPriority(prio::Whenever); break;
		}
	}
	void changeCategory(int index, const std::string& category) { getVec().at(index)->setCategory(category); }
};

#endif