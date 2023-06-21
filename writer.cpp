#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>

int main() {
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char* str = static_cast<char*>(shmat(shmid, nullptr, 0));

    std::cout << "Write Data: ";
    std::string input;
    std::getline(std::cin, input);

    // Copy the input to the shared memory, limiting it to the size of the shared memory
    strncpy(str, input.c_str(), 1023);
    str[1023] = '\0';  // Ensure null-terminated string

    printf("Data written in memory: %s\n", str);

    // Detach from shared memory
    shmdt(str);

    return 0;
}
