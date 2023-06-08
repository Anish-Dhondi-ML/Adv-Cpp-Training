// 08-06-2023
// 4. Set date and time in Linux Operating System using C++ program.

#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Get the current time
    time_t currentTime = time(nullptr);
    struct tm* localTime = localtime(&currentTime);

    // Set the new date and time
    localTime->tm_year = 122;  // Year since 1900 (e.g., 2022 - 1900 = 122)
    localTime->tm_mon = 0;    // Month (0 - 11, January = 0)
    localTime->tm_mday = 1;   // Day of the month (1 - 31)
    localTime->tm_hour = 12;  // Hour (0 - 23)
    localTime->tm_min = 0;    // Minute (0 - 59)
    localTime->tm_sec = 0;    // Second (0 - 59)

    // Convert the modified time back to a time_t value
    time_t newTime = mktime(localTime);

    // Set the new system time using the date command
    std::string setTimeCommand = "date -s @";
    setTimeCommand += std::to_string(newTime);
    std::system(setTimeCommand.c_str());

    std::cout << "New date and time set successfully." << std::endl;

    return 0;
}

