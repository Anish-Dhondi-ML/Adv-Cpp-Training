#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 100  // Define the size of the shared memory segment. We can adjust this value as per our requirements.

int main() {
   
    key_t key = ftok("shared_memory", 1234);
    // Generate a unique key for the shared memory segment using the ftok() function. 
    // The key is based on a file name ("shared_memory") and 
    // a project-specific identifier (1234) which can be anything of our choice.

	if (key == -1) {
    // Key generation failed
    std::cout << "Key generation failed!" << std::endl;
}
    
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    // Create or open the shared memory segment. 
    // The function takes the key, size of the segment, and flags 
    // (IPC_CREAT indicates creation if the segment doesn't exist, and 0666 specifies read and write permissions).
    
    // Condition to check the shared memory id creation.
    if (shmid == -1) {
        std::cerr << "Failed to create/open shared memory segment." << std::endl;
        return 1;
    }

    // attaches the shared memory segment identified by shmid to the process's address space. 
    char* shared_memory = (char*)shmat(shmid, NULL, 0);
    // Since NULL is passed as the shmaddr argument, the operating system will choose a suitable address for the attachment. 
    // The 0 as the shmflg argument specifies the default read/write permissions.
    
    // Condition to check the attachment of shared memory segment.
    if (shared_memory == (char*)-1) {
        std::cerr << "Failed to attach to shared memory segment." << std::endl;
        return 1;
    }


    // Fork multiple processes
    for (int i = 0; i < 2; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            std::cerr << "Failed to fork a child process." << std::endl;
            return 1;
        }
        else if (pid == 0) {
            // Child process
            std::string process_name = (i == 0) ? "Process A" : "Process B";

            while (true) {
                // Read the message from the shared memory segment
                std::string received_message(shared_memory);

                // Check if the received message is an exit signal
                if (received_message == "exit") {
                    std::cout << process_name << ": Exiting..." << std::endl;
                    break;
                }

                // Print the received message
                std::cout << process_name << ": Received message - " << received_message << std::endl;

                // Prompt user for a message to send
                std::cout << process_name << ": Enter a message to send (or type 'exit' to quit): ";
                std::string message;
                std::getline(std::cin, message);

                // Copy the message to the shared memory segment
                std::strcpy(shared_memory, message.c_str());
            }

            // Detach from the shared memory segment
            shmdt(shared_memory);
            return 0;
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < 2; ++i) {
        wait(NULL);
    }

    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);
    	// shmid -It specifies which shared memory segment to perform the control operation on.
	// IPC_RMID is a command that requests the removal (deletion) of the shared memory segment.
	// NULL - The buf argument. NULL is passed because we are not interested in retrieving any information about the segment.
	

    return 0;
}

