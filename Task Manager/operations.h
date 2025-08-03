#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>
#include <atomic>
#include <thread>
#include "manager.h"
/**
 * @class Operation
 * @brief Handles file operations and background autosaving for the task manager.
 *
 * @details This class provides functionality for saving/loading tasks to/from a file,
 * and launching an autosave thread that periodically writes data to disk.
 */
class Operation {
private:
	/// Reference to the Manager instance holding the tasks.
	Manager& manager;
	/// Flag to control the autosave thread.
	std::atomic<bool> doSave{ false };
	/// The autosave thread.
	std::thread autosave;
public:
	/**
	 * @brief Constructs an Operation object.
	 * @param m Reference to a Manager instance.
	 */
	Operation(Manager& m) : manager(m) {}

	/**
	 * @brief Saves all tasks to a file.
	 * @param fileName Path to the file where tasks should be saved.
	 *
	 * @throws std::runtime_error If the file cannot be opened.
	 */
	void save(const std::string& fileName);
	/**
	 * @brief Loads tasks from a file and adds them to the manager.
	 * @param fileName Path to the file to load tasks from.
	 *
	 * @throws std::runtime_error If the file cannot be opened or parsed.
	 */
	void load(const std::string& fileName);

	/**
	* @brief Starts the autosave mechanism in a background thread.
	* @param fileName File path to save to repeatedly.
	*
	* @details Tasks are saved every 5 seconds until `stopAutoSave()` is called.
	*/
	void autoSave(const std::string& fileName);
	/**
	* @brief Stops the autosave thread and waits for it to finish.
	*/
	void stopAutoSave();
};

#endif
