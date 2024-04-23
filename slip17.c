#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int fd[2]; // File descriptors for the pipe
    pid_t pid;
    char message_parent[] = "Hello child!";
    char message_child[] = "Hello parent!";
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        // Close the unused write end of the pipe
        close(fd[0]);

        // Write message to the child
        write(fd[1], message_parent, strlen(message_parent) + 1);

        // Close the write end of the pipe after writing
        close(fd[1]);

        printf("Parent sent message to child.\n");

        // Wait for the child to finish
        wait(NULL);

    } else { // Child process
        // Close the unused read end of the pipe
        close(fd[1]);

        // Read message from the parent
        read(fd[0], buffer, BUFFER_SIZE);
        printf("Child received message: %s\n", buffer);

        // Close the read end of the pipe after reading
        close(fd[0]);

        // Write message to the parent
        write(STDOUT_FILENO, message_child, strlen(message_child) + 1);
        printf("Child sent message to parent.\n");
    }

    return 0;
}
