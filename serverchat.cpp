#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 8080;

int main()
{
    int serverSocket;
    int newSocket;
    char buffer[1024] = {0};
    struct sockaddr_in serverAddress, clientAddress;
    int addrLen = sizeof(clientAddress);

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Failed to bind" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 1) < 0)
    {
        std::cerr << "Failed to listen" << std::endl;
        return -1;
    }

    // Accept a connection
    if ((newSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t *)&addrLen)) < 0)
    {
        std::cerr << "Failed to accept connection" << std::endl;
        return -1;
    }

    // Communication loop
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(newSocket, buffer, sizeof(buffer));
        std::cout << "Client: " << buffer << std::endl;

        // Check if client wants to terminate the session
        if (strcmp(buffer, "BYE") == 0)
        {
            std::cout << "Session terminated by client" << std::endl;
            break;
        }

        std::string serverMessage;
        std::cout << "Enter server message: ";
        std::getline(std::cin, serverMessage);

        // Send server message to client
        send(newSocket, serverMessage.c_str(), serverMessage.length(), 0);
    }

    close(newSocket);
    close(serverSocket);
    return 0;
}
