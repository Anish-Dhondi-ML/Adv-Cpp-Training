 // Reading date and time from Linux operating system using C++ program.

#include <iostream>
#include <ctime>

int main() {

    // Get the current system time
    std::time_t currentTime = std::time(nullptr);

    // Convert the system time to local time
    std::tm* localTime = std::localtime(&currentTime);

    // Extract individual components of the local time
    int year = localTime->tm_year + 1900;   // Year since 1900
    int month = localTime->tm_mon + 1;      // Month (0-11)
    int day = localTime->tm_mday;           // Day of the month (1-31)
    int hour = localTime->tm_hour;          // Hour (0-23)
    int minute = localTime->tm_min;         // Minute (0-59)
    int second = localTime->tm_sec;         // Second (0-59)

    // Print the current date and time
    std::cout << "Current date and time: ";
    std::cout << year << "-" << month << "-" << day << " ";
    std::cout << hour << ":" << minute << ":" << second << std::endl;

    return 0;
}

