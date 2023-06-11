#include <iostream>
#include <vector>

template<typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> intVector = {1, 2, 3, 4, 5};
    std::vector<std::string> stringVector = {"Hello", "World"};

    std::cout << "Int Vector: ";
    printVector(intVector); // Prints: 1 2 3 4 5

    std::cout << "String Vector: ";
    printVector(stringVector); // Prints: Hello World

    return 0;
}
