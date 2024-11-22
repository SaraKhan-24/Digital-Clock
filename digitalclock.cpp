#include "digitalclock.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto today_duration = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()) % std::chrono::hours(24);
    auto hours = std::chrono::duration_cast<std::chrono::hours>(today_duration).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(today_duration).count() % 60;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(today_duration).count() % 60;

    int time_zone_offset = 5; // Adjust this to your local time zone offset
    hours += time_zone_offset;
    if (hours >= 24) hours -= 24;

    int display_hours = (hours % 12 == 0) ? 12 : hours % 12;
    std::string am_pm = (hours < 12) ? "AM" : "PM";

    std::ostringstream time_stream;
    time_stream << display_hours << " : "
                << std::setw(2) << std::setfill('0') << minutes << " : "
                << std::setw(2) << std::setfill('0') << seconds << " "
                << am_pm;

    return time_stream.str();
}
