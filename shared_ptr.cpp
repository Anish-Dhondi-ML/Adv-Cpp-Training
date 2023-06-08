// Using shared_ptr

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

void func(std::shared_ptr<MyClass> ptr) {
    std::cout << "Shared pointer use count: " << ptr.use_count() << std::endl;
    ptr->doSomething();
}

int main() {
    std::shared_ptr<MyClass> sharedPtr1 = std::make_shared<MyClass>();
    std::cout << "Shared pointer 1 use count: " << sharedPtr1.use_count() << std::endl;

    {
        std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1;
        std::cout << "Shared pointer 1 use count: " << sharedPtr1.use_count() << std::endl;
        std::cout << "Shared pointer 2 use count: " << sharedPtr2.use_count() << std::endl;

        func(sharedPtr1);
    }

    std::cout << "Shared pointer 1 use count: " << sharedPtr1.use_count() << std::endl;

    return 0;
}
