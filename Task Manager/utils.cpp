#include "utils.h"
#include "task.h"
#include <memory>
#include <sstream>

std::string plural(int value, const std::string& singular, const std::string& pluralForm) {
    return value == 1 ? singular : pluralForm;
}

std::string priorityToString(prio p) {
    switch (p) {
    case prio::ASAP: return "ASAP";
    case prio::Later: return "Later";
    case prio::Whenever: return "Whenever";
    default: return "Unknown";
    }
}

std::string deadlineToString(std::chrono::system_clock::time_point tp) {
    using namespace std::chrono;

    std::ostringstream oss;
    if (tp == system_clock::time_point{}) {
        oss << "--";
        return oss.str();
    }

    auto now = system_clock::now();
    auto diff = duration_cast<seconds>(tp - now);
    auto secondsLeft = diff.count();

    if (secondsLeft < 0) return "The deadline has already passed.";

    int days = secondsLeft / (24 * 3600);
    int hours = (secondsLeft % (24 * 3600)) / 3600;
    int minutes = (secondsLeft % 3600) / 60;

    int parts = 0;

    if (days > 0) {
        oss << days << " " << plural(days, "day", "days");
        ++parts;
    }
    if (hours > 0) {
        if (parts > 0) oss << (minutes > 0 ? ", " : " and ");
        oss << hours << " " << plural(hours, "hour", "hours");
        ++parts;
    }
    if (minutes > 0) {
        if (parts > 0) oss << " and ";
        oss << minutes << " " << plural(minutes, "minute", "minutes");
    }
    if (days == 0 && hours == 0 && minutes == 0) {
        return "Less than a minute remaining.";
    }

    return oss.str();
}

std::string formatDeadline(const system_clock::time_point& tp) {
    std::time_t time = system_clock::to_time_t(tp);
    std::tm* tm = std::localtime(&time);

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << tm->tm_mday << "-"
        << std::setw(2) << tm->tm_mon + 1 << "-"
        << (tm->tm_year + 1900) << ","
        << std::setw(2) << tm->tm_hour << ":"
        << std::setw(2) << tm->tm_min;

    return oss.str();
}
