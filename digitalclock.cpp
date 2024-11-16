#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;

int main() {
    // Get the current time in UTC (system clock)
    auto now = chrono::system_clock::now();

    // Convert system time to seconds since epoch
    auto today_duration = chrono::duration_cast<chrono::seconds>(now.time_since_epoch()) % chrono::hours(24);

    // Convert the duration into hours, minutes, and seconds
    auto hours = chrono::duration_cast<chrono::hours>(today_duration).count();
    auto minutes = chrono::duration_cast<chrono::minutes>(today_duration).count() % 60;
    auto seconds = chrono::duration_cast<chrono::seconds>(today_duration).count() % 60;

    // Adjust for your local time zone manually (example: UTC+5)
    int time_zone_offset = 5; // Adjust this to your local time zone offset
    hours += time_zone_offset;

    // Handle the case for wrap-around when hours exceed 24
    if (hours >= 24) {
        hours -= 24;
    }

    // Format hours for 12-hour clock
    int display_hours = (hours % 12 == 0) ? 12 : hours % 12;
    string am_pm = (hours < 12) ? "AM" : "PM";

    // Display the time in 12-hour format
    cout << "Current Time: " << display_hours << " : "
         << setw(2) << setfill('0') << minutes << " : "
         << setw(2) << setfill('0') << seconds << " "
         << am_pm << endl;

    return 0;
}
