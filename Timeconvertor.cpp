// 08-06-2023
// 3. Program to create class to read time in seconds and convert into time in (HH:MM:SS) format. Using Smart Pointers

#include <iostream>
#include <memory>

class TimeConverter {
private:
    int totalSeconds;

public:
    TimeConverter(int seconds) : totalSeconds(seconds) {}

    std::string ConvertToHHMMSS() const {
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds % 3600) / 60;
        int seconds = totalSeconds % 60;

        std::string timeString = FormatTime(hours) + ":" + FormatTime(minutes) + ":" + FormatTime(seconds);
        return timeString;
    }

private:
    std::string FormatTime(int value) const {
        if (value < 10) {
            return "0" + std::to_string(value);
        }
        return std::to_string(value);
    }
};

int main() {
    int seconds;
    std::cout << "Enter the time in seconds: ";
    std::cin >> seconds;

    std::shared_ptr<TimeConverter> timeConverter = std::make_shared<TimeConverter>(seconds);
    std::string formattedTime = timeConverter->ConvertToHHMMSS();

    std::cout << "Formatted time: " << formattedTime << std::endl;

    return 0;
}
