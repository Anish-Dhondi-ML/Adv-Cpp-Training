#include <iostream>
#include <string>

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance; // This line ensures the instance is created only once
        return instance;
    }

    void log(const std::string& message) {
        for(int i = 0 ; i < 3 ; i++)
        std::cout <<i+1<<"."<< message << std::endl;
    }

private:
    Logger() {} // Private constructor
    Logger(const Logger&) = delete; // Disable copy constructor
    Logger& operator=(const Logger&) = delete; // Disable assignment operator
};

int main() {
    Logger& logger = Logger::getInstance();
    logger.log("This is a log message");

    return 0;
}
