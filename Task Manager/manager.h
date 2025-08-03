#ifndef MANAGER_H
#define MANAGER_H

#include "task.h"
#include <vector>
#include <memory>
/**
 * @class Manager
 * @brief Manages a collection of tasks.
 * @details Provides functionality to add, remove, and modify tasks. Stores tasks internally using smart pointers.
 */
class Manager {
private:
	/// Internal list of tasks.
	std::vector<std::unique_ptr<Task>> vecTask;
public:
	/// Default constructor.
	Manager() = default;
	/**
	 * @brief Provides access to the internal task vector.
	 * @return A reference to the vector of unique pointers to tasks.
	 */
	std::vector<std::unique_ptr<Task>>& getVec() { return vecTask; }

	/**
	 * @brief Adds a new task with the given name.
	 * @param n The name of the task to add.
	 */
	void addTask(std::string n) { vecTask.emplace_back(std::make_unique<Task>(std::move(n))); }
	/**
	 * @brief Deletes the task at the given index.
	 * @param index The index of the task to remove.
	 */
	void deleteTask(int index) { vecTask.erase(vecTask.begin() + index); }

	/**
	* @brief Changes either the name or the description of a task.
	* @param index Index of the task to modify.
	* @param what If 1, changes the name; if 2, changes the description.
	* @param name New name or description to apply.
	*/
	void changeNameORDesc(int index, int what, const std::string& name);
	/**
	* @brief Changes the priority of a task.
	* @param index Index of the task to modify.
	* @param what 1 = ASAP, 2 = Later, 3 = Whenever.
	*/
	void changePriority(int index, int what);
	/**
	* @brief Changes the category of a task.
	* @param index Index of the task to modify.
	* @param category The new category name.
	*/
	void changeCategory(int index, const std::string& category);
	/**
	* @brief Changes the completion status of a task.
	* @param index Index of the task to modify.
	*/
	void changeDone(int index);
	/**
	 * @brief Sets the deadline of a task based on date and time components.
	 * @param day Day of the deadline.
	 * @param month Month of the deadline.
	 * @param year Year of the deadline.
	 * @param hour Hour of the deadline.
	 * @param minute Minute of the deadline.
	 * @param index Index of the task to update.
	 */
	void setTPfromSTR(int day, int month, int year, int hour, int minute, int index);
};

#endif
