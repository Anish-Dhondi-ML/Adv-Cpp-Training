#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const char *SERVER_IP = "127.0.0.1";
const int PORT = 8080;

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[1024] = {0};

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Convert IP address from text to binary format
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0)
    {
        std::cerr << "Invalid address or address not supported" << std::endl;
        return -1;
    }

    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    // Communication loop
    while (true)
    {
        std::string clientMessage;
        std::cout << "Enter client message: ";
        std::getline(std::cin, clientMessage);

        // Send client message to server
        send(clientSocket, clientMessage.c_str(), clientMessage.length(), 0);

        // Check if client wants to terminate the session
        if (clientMessage == "BYE")
        {
            std::cout << "Session terminated" << std::endl;
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        int valread = read(clientSocket, buffer, sizeof(buffer));
        std::cout << "Server: " << buffer << std::endl;
    }

    close(clientSocket);
    return 0;
}
