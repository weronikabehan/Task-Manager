#include "operations.h"

#include <fstream>
#include <sstream>

void Operation::save(const std::string& fileName) {
	std::ofstream file(fileName);
	if (!file) throw std::runtime_error("Unable to open the file.");
	
	for (auto& t : manager.getVec()) {
		file << t->getName() << ';' << t->getDone() << ';' << t->getDescription() << ';'
			<< t->getCategory() << ';' << t->priorityToString(t->getPriority()) << std::endl;
	}

	file.close();
}

void Operation::load(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file) throw std::runtime_error("Unable to open the file.");

	std::string line;
	while (std::getline(file, line)) {
		std::string name, description, category, prioritySTR, doneSTR;
		std::stringstream ss(line);

		std::getline(ss, name, ';');
		std::getline(ss, doneSTR, ';');
		std::getline(ss, description, ';');
		std::getline(ss, category, ';');
		std::getline(ss, prioritySTR, ';');

		bool done;
		prio priority;

		(doneSTR == "1") ? done = true : done = false;

		if (prioritySTR == "ASAP") priority = prio::ASAP;
		else if (prioritySTR == "Later") priority = prio::Later;
		else priority = prio::Whenever;

		auto task = std::make_unique<Task>(name);
		task->setDescription(description);
		task->setDone(done);
		task->setCategory(category);
		task->setPriority(priority);
		
		manager.getVec().emplace_back(task);
	}
}

void Operation::autoSave(const std::string& fileName) {
	if (doSave) return;
	doSave = true;
	autosave = std::thread([this, fileName]() {
		while (doSave) {
			try { save(fileName); }
			catch (std::runtime_error) {}
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
		});
}

void Operation::stopAutoSave() {
	if (doSave) {
		doSave = false;
		if (autosave.joinable()) autosave.join();
	}
}