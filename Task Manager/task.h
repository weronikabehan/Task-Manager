#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>
#include <sstream>
using namespace std::chrono;
/**
 * @enum prio
 * @brief Represents the priority levels of a task.
 */
enum class prio {
	ASAP,		///< Task should be done as soon as possible.
	Later,		///< Task can be done later.
	Whenever	///< Task has no specific urgency.
};
/**
 * @class Task
 * @brief Represents a single task with name, status, deadline, etc.
 *
 * @details A task holds information such as its name, description, category,
 * completion status, priority, and an optional deadline.
 */
class Task {
private:
	std::string name;                       ///< Name/title of the task.
	std::string description;                ///< Optional description of the task.
	std::string category;                   ///< Category tag for organization.
	bool done;                              ///< Indicates if the task is completed.
	prio priority;                          ///< Task priority.
	system_clock::time_point deadline;      ///< Optional deadline for the task.
public:
	/**
	* @brief Constructs a new Task with the given name.
	* @param n The name/title of the task.
	*
	* @details Other fields are initialized with default values:
	* - description: "--"
	* - category: "--"
	* - done: false
	* - priority: prio::Whenever
	* - deadline: empty time_point
	*/
	Task(std::string n) : name(n), description("--"), category("--"), done(false), priority(prio::Whenever), deadline(system_clock::time_point{}) {}

	/// @brief Sets the task name.
	/// @param n New name.
	void setName(std::string n) { name = n; }
	/// @brief Sets the task description.
	/// @param d New description.
	void setDescription(std::string d) { description = d; }
	/// @brief Sets the task category.
	/// @param c New category.
	void setCategory(std::string c) { category = c; }
	/// @brief Sets the task completion status.
	/// @param d `true` if done, `false` if not.
	void setDone(bool d) { done = d; }
	/// @brief Sets the task priority.
	/// @param p New priority level.
	void setPriority(prio p) { priority = p; }
	/// @brief Sets the deadline of the task.
	/// @param d New deadline as a `system_clock::time_point`.
	void setDeadline(system_clock::time_point d) { deadline = d; }

	/// @brief Gets the task name.
	/// @return Task name as string.
	std::string getName() const { return name; }
	/// @brief Gets the task description.
	/// @return Task description.
	std::string getDescription() const { return description; }
	/// @brief Gets the task category.
	/// @return Category as string.
	std::string getCategory() const { return category; }
	/// @brief Gets the completion status of the task.
	/// @return `true` if done, `false` otherwise.
	bool getDone() const { return done; }
	/// @brief Gets the task priority.
	/// @return Priority as `prio` enum.
	prio getPriority() const { return priority; }
	/// @brief Gets the deadline.
   /// @return Deadline as `system_clock::time_point`.
	system_clock::time_point getDeadline() const { return deadline; }

	/// @brief Default destructor.
	~Task() = default;
};

#endif
