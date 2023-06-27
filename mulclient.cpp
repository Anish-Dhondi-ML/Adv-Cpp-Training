#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

constexpr int BUFFER_SIZE = 1024;

int main() {
    // Create a socket for the client
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create client socket." << std::endl;
        return 1;
    }

    // Set up server address and port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Invalid server address." << std::endl;
        close(clientSocket);
        return 1;
    }

    // Connect to the server
    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to connect to the server." << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected to the server." << std::endl;

    // Send and receive data
    char buffer[BUFFER_SIZE];
    while (true) {
        std::string message;
        std::cout << "Enter message (or 'q' to quit): ";
        std::getline(std::cin, message);

        if (message == "q") {
            break;
        }

        // Send the message to the server
        ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
        if (bytesSent < 0) {
            std::cerr << "Failed to send message to the server." << std::endl;
            close(clientSocket);
            return 1;
        }

        // Receive the echoed message from the server
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            std::cerr << "Failed to receive message from the server." << std::endl;
            close(clientSocket);
            return 1;
        }

        std::cout << "Server echoed: " << buffer << std::endl;
    }

    // Close the client socket
    close(clientSocket);

    return 0;
}

