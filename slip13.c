#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {  // Child process
        // Execute the command passed as argument
        if (execvp(argv[1], &argv[1]) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {  // Parent process
        // Wait for the child to complete
        waitpid(pid, &status, 0);

        // Print child pid and exit status
        printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));

        // Print parent pid
        printf("Parent process pid: %d\n", getpid());
    }

    return 0;
}
