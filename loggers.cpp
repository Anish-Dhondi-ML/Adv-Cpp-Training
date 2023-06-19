#include <iostream>
#include <string>

class Logger {
public:
    std::string  name, loves;
    static Logger& getInstance() {
        static Logger instance; // This line ensures the instance is created only once
        return instance;
    }

    void setValues(std::string name,
                 std::string loves)
  {
    this->name = name;
    this->loves = loves;
  }
   
  // prints values of member variables
  void print()
  {
    std::cout << name << " Loves " <<
            loves << "." <<std:: endl;
  }

private:
    
    Logger() {} // Private constructor
    Logger(const Logger&) = delete; // Disable copy constructor
    Logger& operator=(const Logger&) = delete; // Disable assignment operator
};

int main() {
    Logger& logger = Logger::getInstance();
    
    logger.setValues("This is a log message", "Hey");
    logger.print();
    std::cout << "Address of logger: " <<&logger << std::endl;
    std::cout << std::endl;
    Logger& logger1 = Logger::getInstance();
    logger1.setValues("Hello world", "Hi");
    logger1.print();
    std::cout << "Address of logger1: " <<&logger1 << std::endl;
    std::cout << std::endl;
    Logger& logger2 = Logger::getInstance();
    logger2.setValues("All is Well", "Hello");
    logger2.print();
    std::cout << "Address of logger2: " <<&logger2 << std::endl;
    std::cout << std::endl;

    return 0;
}
