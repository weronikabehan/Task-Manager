#include "operations.h"
#include "utils.h"

#include <fstream>
#include <sstream>

void Operation::save(const std::string& fileName) {
	std::ofstream file(fileName);
	if (!file) throw std::runtime_error("Unable to open the file.");
	
	for (auto& t : manager.getVec()) {
		file << t->getName() << ';' << t->getDone() << ';' << t->getDescription() << ';'
			<< t->getCategory() << ';' << priorityToString(t->getPriority()) << ';' <<
			formatDeadline(t->getDeadline()) << std::endl;
	}

	file.close();
}

void Operation::load(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file) throw std::runtime_error("Unable to open the file.");

	std::string line;
	while (std::getline(file, line)) {
		std::string name, description, category, prioritySTR, doneSTR, deadlineSTR;
		std::stringstream ss(line);

		std::getline(ss, name, ';');
		std::getline(ss, doneSTR, ';');
		std::getline(ss, description, ';');
		std::getline(ss, category, ';');
		std::getline(ss, prioritySTR, ';');
		std::getline(ss, deadlineSTR);

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

		if (!deadlineSTR.empty()) {
			std::stringstream dateSS(deadlineSTR);
			std::string temp;
			int day, month, year, hour, minute;

			std::getline(dateSS, temp, '-');
			day = std::stoi(temp);
			std::getline(dateSS, temp, '-');
			month = std::stoi(temp);
			std::getline(dateSS, temp, ',');
			year = std::stoi(temp);

			std::getline(dateSS, temp, ':');
			hour = std::stoi(temp);
			std::getline(dateSS, temp);
			minute = std::stoi(temp);

			std::tm tm = {};
			tm.tm_year = year - 1900;
			tm.tm_mon = month - 1;
			tm.tm_mday = day;
			tm.tm_hour = hour;
			tm.tm_min = minute;

			std::time_t time = std::mktime(&tm);
			system_clock::time_point tp = system_clock::from_time_t(time);
			task->setDeadline(tp);
		}
		
		manager.getVec().emplace_back(std::move(task));
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
