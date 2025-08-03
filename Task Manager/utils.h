#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>
#include "task.h"
/**
 * @brief Chooses correct singular or plural form of a word based on a number.
 *
 * @param value The numeric value (e.g. 1 or 5).
 * @param singular The word to use if value == 1.
 * @param pluralForm The word to use otherwise.
 * @return Correct word form as string.
 */
std::string plural(int value, const std::string& singular, const std::string& pluralForm);
/**
 * @brief Converts a deadline into a human-readable string like "2 days and 4 hours".
 *
 * @param tp The deadline time point.
 * @return String describing how much time is left or if it has passed.
 */
std::string deadlineToString(std::chrono::system_clock::time_point tp);
/**
 * @brief Converts a priority enum to its string representation.
 *
 * @param p The priority enum value.
 * @return "ASAP", "Later", or "Whenever".
 */
std::string priorityToString(prio p);
/**
 * @brief Formats a time_point into a fixed string format: dd-mm-yyyy,hh:mm.
 *
 * @param tp The time point to format.
 * @return Formatted string representing date and time.
 */
std::string formatDeadline(const system_clock::time_point& tp);

#endif
