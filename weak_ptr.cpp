// Using weak_ptr

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

void func(std::shared_ptr<MyClass> sharedPtr, std::weak_ptr<MyClass> weakPtr) {
    std::cout << "Shared pointer use count: " << sharedPtr.use_count() << std::endl;

    // Check if weakPtr is expired before using it
    if (auto lockedPtr = weakPtr.lock()) {
        std::cout << "Weak pointer is valid" << std::endl;
        lockedPtr->doSomething();
    } else {
        std::cout << "Weak pointer is expired" << std::endl;
    }
}



int main() {
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> weakPtr = sharedPtr;

    func(sharedPtr, weakPtr);

    sharedPtr.reset();  // Release the shared ownership

    func(sharedPtr, weakPtr);

    return 0;
}
