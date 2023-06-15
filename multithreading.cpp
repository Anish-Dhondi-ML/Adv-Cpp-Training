#include <iostream>
#include <thread>

// Function to count from start to end
void countNumbers(int start, int end, int interval) {
    for (int i = start; i <= end; i += interval) {
        std::cout << i << " ";
    }
}

int main() {
    // Create two threads
    std::thread thread1(countNumbers, 1, 10, 2);  // Counts odd numbers
    std::thread thread2(countNumbers, 2, 10, 2);  // Counts even numbers

    // Wait for both threads to finish
    thread1.join();
    thread2.join();

    std::cout << std::endl;

    return 0;
}
