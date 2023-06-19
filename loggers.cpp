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
    std::cout << "Address of logger: " <<&logger << std::endl;
    std::cout << std::endl;
    Logger& logger1 = Logger::getInstance();
    logger1.log("Hello world");
    std::cout << "Address of logger1: " <<&logger1 << std::endl;
    std::cout << std::endl;
    Logger& logger2 = Logger::getInstance();
    logger1.log("All is Well");
    std::cout << "Address of logger2: " <<&logger2 << std::endl;
    std::cout << std::endl;

    return 0;
}
