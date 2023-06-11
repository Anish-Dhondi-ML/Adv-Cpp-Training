#include <iostream>
#include <map>

template<typename Key, typename Value>
void printMap(const std::map<Key, Value>& myMap) {
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int main() {
    std::map<std::string, int> myMap = {
        {"Anish", 825},
        {"Mithil", 430},
        {"Bondy", 935}
    };

    std::cout << "Map Contents:" << std::endl;
    printMap(myMap);

    return 0;
}
