// 07-06-2023
// 1. Program to demonstrate the usage of smart pointer and its significance over normal pointer.



#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructed" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destroyed" << std::endl;
    }

    void doSomething() {
        std::cout << "Doing something..." << std::endl;
    }
};

int main() {
    // Using a raw pointer
    MyClass* rawPtr = new MyClass();
    rawPtr->doSomething();
    delete rawPtr;

    std::cout << std::endl;

    // Using a smart pointer (unique_ptr)
    std::unique_ptr<MyClass> smartPtr = std::make_unique<MyClass>();
    smartPtr->doSomething();

    return 0;
}
