#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool isEvenPrinted = false;

void printEvenNumbers() {
    for (int i = 0; i <= 10; i += 2) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !isEvenPrinted; }); // Wait until the previous even number is printed

        std::cout << i << " ";

        isEvenPrinted = true;
        cv.notify_one(); // Notify the other thread to print the next odd number
    }
}

void printOddNumbers() {
    for (int i = 1; i <= 10; i += 2) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return isEvenPrinted; }); // Wait until the previous even number is printed

        std::cout << i << " ";

        isEvenPrinted = false;
        cv.notify_one(); // Notify the other thread to print the next even number
    }
}

int main() {
    std::thread t1(printEvenNumbers);
    std::thread t2(printOddNumbers);

    t1.join();
    t2.join();

    std::cout << std::endl;

    return 0;
}

