#ifndef INTERFACE_H
#define INTERFACE_H

#include "manager.h"

/**
 * @brief Displays the main application menu.
 * @details Lists available actions for the user such as adding, deleting, or editing tasks.
 */
void showMenu();
/**
 * @brief Gets the user's input and validates it within a range.
 *
 * @param min The minimum allowed value.
 * @param max The maximum allowed value.
 * @return The validated integer input.
 *
 * @throws std::out_of_range If the input is outside the given range.
 * @throws std::invalid_argument If the input is not a valid number.
 */
int validChoice(int min, int max);
/**
 * @brief Displays all tasks currently managed.
 *
 * @param manager A reference to the Manager containing tasks.
 */
void showTasks(Manager& manager);
/**
 * @brief Allows the user to choose from existing task categories.
 *
 * @param manager A reference to the Manager used to retrieve available categories.
 * @return The selected category or "--" if no categories are available.
 */
std::string chooseExistingCategory(Manager& manager);

/**
 * @brief Handles the process of adding a new task.
 *
 * @param manager A reference to the Manager where the task will be added.
 *
 * @throws std::invalid_argument If the user provides an empty task name.
 */
void IF_add(Manager& manager);
/**
 * @brief Handles deletion of a task selected by the user.
 *
 * @param manager A reference to the Manager from which the task will be removed.
 */
void IF_delete(Manager& manager);
/**
 * @brief Allows the user to edit an existing task.
 *
 * @param manager A reference to the Manager containing the task.
 */
void IF_edit(Manager& manager);
/**
 * @brief Toggles a task's completion status (done / not done).
 *
 * @param manager A reference to the Manager containing the task.
 */
void IF_done(Manager& manager);
/**
 * @brief Prompts the user for a date and time and sets it as the task's deadline.
 *
 * @param manager A reference to the Manager containing the task.
 * @param index The index of the task to update.
 */
void IF_getDate(Manager& manager, int index);

#endif