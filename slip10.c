#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file for writing (create it if it doesn't exist, truncate it to zero length if it does)
    int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (file_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Redirect standard output to the file using dup2
    if (dup2(file_fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(file_fd);
        exit(EXIT_FAILURE);
    }

    // Now, any output written to stdout will be redirected to the file output.txt
    printf("This text will be written to output.txt\n");
    printf("Redirecting standard output to a file using dup and open system calls.\n");

    // Close the file descriptor
    close(file_fd);

    return 0;
}
