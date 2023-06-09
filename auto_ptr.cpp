// By Using auto_ptr

#include <iostream>
#include <memory>

int main() {
    std::auto_ptr<int> ptr(new int(42));

    std::cout << "Value: " << *ptr << std::endl;

    ptr.reset(new int(99));

    std::cout << "New value: " << *ptr << std::endl;

    return 0;
}
