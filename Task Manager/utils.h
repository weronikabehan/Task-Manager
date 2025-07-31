#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>
#include "task.h"

std::string plural(int value, const std::string& singular, const std::string& pluralForm);
std::string deadlineToString(std::chrono::system_clock::time_point tp);
std::string priorityToString(prio p);

#endif
