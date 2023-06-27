#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

constexpr int MAX_CLIENTS = 100;
constexpr int BUFFER_SIZE = 1024;

int main() {
    // Create a socket for the server
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET specifies the address family,IPv4. Other AF_INET6 for IPv6.
    // SOCK_STREAM specifies the socket type, stream socket, which provides a reliable, connection-oriented communication channel.SOCK_DGRAM for a datagram socket,provides an unreliable, connectionless communication channel.
    // 0 is passed to let the system choose the default protocol.
    
    if (serverSocket == -1) {
        std::cerr << "Failed to create server socket." << std::endl;
        return 1;
    }

    // Set up server address and port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345); //12345 is being converted from host byte order to network byte order. 
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the server socket to the specified address and port
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0)
    // serverSocket is the socket descriptor representing the socket we want to bind.
    // reinterpret_cast<sockaddr*>(&serverAddress) to convert the serverAddress structure to a pointer of type sockaddr*
    
     {
        std::cerr << "Failed to bind server socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, MAX_CLIENTS) < 0)
    // MAX_CLIENTS determines the maximum number of connections that can be waiting in the listen queue.
     {
        std::cerr << "Failed to listen for connections." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server started. Listening for connections..." << std::endl;

    // Set of client sockets
    int clientSockets[MAX_CLIENTS] = {0};
    fd_set socketSet;
    int maxSocket = serverSocket;

    // Accept incoming connections and handle data
    while (true) {
        // Clear the socket set and add the server socket
        FD_ZERO(&socketSet);
        FD_SET(serverSocket, &socketSet);

        // Add connected client sockets to the socket set
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            int clientSocket = clientSockets[i];
            if (clientSocket > 0) {
                FD_SET(clientSocket, &socketSet);
                if (clientSocket > maxSocket)
                    maxSocket = clientSocket;
            }
        }

        // Monitor the socket set for activity
        int activity = select(maxSocket + 1, &socketSet, nullptr, nullptr, nullptr);
        if (activity < 0) {
            std::cerr << "Failed to monitor sockets for activity." << std::endl;
            close(serverSocket);
            return 1;
        }

        // Handle new connections
        if (FD_ISSET(serverSocket, &socketSet)) {
            // Accept the new connection
            sockaddr_in clientAddress{};
            socklen_t addressLength = sizeof(clientAddress);
            int newClientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &addressLength);
            if (newClientSocket < 0) {
                std::cerr << "Failed to accept new connection." << std::endl;
                close(serverSocket);
                return 1;
            }

            // Add the new client socket to the array
            for (int i = 0; i < MAX_CLIENTS; ++i) {
                if (clientSockets[i] == 0) {
                    clientSockets[i] = newClientSocket;
                    std::cout << "New connection: " << inet_ntoa(clientAddress.sin_addr) << ", socket fd: " << newClientSocket << std::endl;
                    break;
                }
            }
        }

        // Handle data from connected clients
        char buffer[BUFFER_SIZE];
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            int clientSocket = clientSockets[i];
            if (FD_ISSET(clientSocket, &socketSet)) {
                // Receive data from the client
                memset(buffer, 0, sizeof(buffer));
                ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0) {
                    // Connection closed or error occurred
                    sockaddr_in clientAddress{};
                    socklen_t addressLength = sizeof(clientAddress);
                    getpeername(clientSocket, reinterpret_cast<sockaddr*>(&clientAddress), &addressLength);
                    std::cout << "Client disconnected: " << inet_ntoa(clientAddress.sin_addr) << ", socket fd: " << clientSocket << std::endl;

                    // Close the socket and remove it from the array
                    close(clientSocket);
                    clientSockets[i] = 0;
                } else {
                    // Handle received data
                    std::cout << "Received message from client " << clientSocket << ": " << buffer << std::endl;
		std::string response;
        	std::cout << "Enter Response Message to "<<clientSocket<<": ";
        	std::getline(std::cin, response);

                    // Send the response message back to the client
                    send(clientSocket, response.c_str(), response.length(), 0);
                }
            }
        }
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}

