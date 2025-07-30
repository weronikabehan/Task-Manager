#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>
#include <atomic>
#include <thread>
#include "manager.h"

class Operation {
private:
	Manager& manager;
	std::atomic<bool> doSave{ false };
	std::thread autosave;
public:
	Operation(Manager& m) : manager(m) {}

	void save(const std::string& fileName);
	void load(const std::string& fileName);

	void autoSave(const std::string& fileName);
	void stopAutoSave();
};

#endif