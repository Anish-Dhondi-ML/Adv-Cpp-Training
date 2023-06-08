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
    //After creating sharedPtr1 using std::make_shared<MyClass>(), 
    //the reference count is 1. This is because sharedPtr1 is the only shared pointer owning the object.
    std::shared_ptr<MyClass> sharedPtr1 = std::make_shared<MyClass>();
    std::cout << "Shared pointer 1 use count: " << sharedPtr1.use_count() << std::endl;

    {   
        // sharedPtr2 is created and initialized with sharedPtr1.
        // Both sharedPtr1 and sharedPtr2 share ownership of the object, so the reference count becomes 2 for both of them.
        std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1;
        std::cout << "Shared pointer 1 use count: " << sharedPtr1.use_count() << std::endl;
        std::cout << "Shared pointer 2 use count: " << sharedPtr2.use_count() << std::endl;
        
        // When func() is called with sharedPtr1 as an argument, sharedPtr1 is passed by value, which creates a copy of the shared pointer. 
        // The reference count increases to 3 because func() now also holds a shared ownership of the object.
        func(sharedPtr1);
    }
    // As the nested scope ends, sharedPtr2 goes out of scope and is destroyed. The reference count decreases to 1
    // sharedPtr1 is still in scope. The reference count remains 1, 
    // indicating that sharedPtr1 is the only shared pointer that continues to own the object.
    std::cout << "Shared pointer 1 use count: " << sharedPtr1.use_count() << std::endl;

    return 0;
}
