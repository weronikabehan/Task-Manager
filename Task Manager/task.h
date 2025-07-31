#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>
#include <sstream>
using namespace std::chrono;

enum class prio { ASAP, Later, Whenever };

class Task {
private:
	std::string name;
	std::string description;
	std::string category;
	bool done;
	prio priority;
public:
	Task(std::string n) : name(n), description("--"), category("--"), done(false), priority(prio::Whenever) {}

	void setName(std::string n) { name = n; }
	void setDescription(std::string d) { description = d; }
	void setCategory(std::string c) { category = c; }
	void setDone(bool d) { done = d; }
	void setPriority(prio p) { priority = p; }

	std::string getName() const { return name; }
	std::string getDescription() const { return description; }
	std::string getCategory() const { return category; }
	bool getDone() const { return done; }
	prio getPriority() const { return priority; }

	std::string priorityToString(prio p) {
		switch (p) {
		case prio::ASAP: return "ASAP";
		case prio::Later: return "Later";
		case prio::Whenever: return "Whenever";
		default: return "Unknown";
		}
	}

	~Task() = default;
};

#endif