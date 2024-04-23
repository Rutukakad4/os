#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Close the read end of the pipe
        close(pipefd[0]);
        
        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        
        // Close unused file descriptors
        close(pipefd[1]);
        
        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
        
        // execlp() only returns if an error occurs
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Close the write end of the pipe
        close(pipefd[1]);
        
        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        
        // Close unused file descriptors
        close(pipefd[0]);
        
        // Execute wc -l
        execlp("wc", "wc", "-l", NULL);
        
        // execlp() only returns if an error occurs
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
