#include <iostream>
#include <csignal>

// Global variable to track whether a signal has been received
volatile sig_atomic_t signalReceived = 0;

// Signal handler function
void signalHandler(int signalNumber) {
    // Set the signalReceived flag to indicate a signal was received
    signalReceived = signalNumber;
}

int main() {
    // Register signal handlers
    
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    std::signal(SIGSEGV, signalHandler);

    // Problem:  trying to modify read only memory which causing Segmentation Fault //
    char* str;
    str = "GfG";
    *(str + 1) = 'n';


    // Infinite loop to keep the program running until a signal is received
    while (signalReceived == 0) {
        // Do some work here
    }

    // Handling the received signal
    switch (signalReceived) {
        case SIGINT:
            std::cout << "Received SIGINT signal. Exiting gracefully..." << std::endl;
            // Perform cleanup or any necessary actions
            break;
        case SIGTERM:
            std::cout << "Received SIGTERM signal. Terminating gracefully..." << std::endl;
            // Perform cleanup or any necessary actions
            break;
        case SIGSEGV:
            std::cout << "Received SIGSEGV signal. Segmentation fault occurred!" << std::endl;
            // Perform cleanup or any necessary actions
            break;
        default:
            std::cout << "Received an unknown signal: " << signalReceived << std::endl;
            // Perform cleanup or any necessary actions
            break;
    }

    return 0;
}
