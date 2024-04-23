#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2]; // File descriptors for the pipe
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]); 
        char *messages[] = {"Hello World", "Hello SPPU", "Linux is Funny"};
        for (int i = 0; i < 3; i++) {
            write(pipefd[1], messages[i], strlen(messages[i]));
            write(pipefd[1], "\n", 1); // Write a newline after each message
        }
   close(pipefd[1]); // Close writing end in the child
        exit(EXIT_SUCCESS);
    } else {
        close(pipefd[1]); // Close writing end in the parent

        printf("Messages received from child process:\n");

        while (read(pipefd[0], buffer, BUFFER_SIZE) > 0) {
            printf("%s", buffer);
        }

        printf("\n");

        close(pipefd[0]); // Close reading end in the parent
        wait(NULL); // Wait for child process to finish
    }

    return 0;
}
