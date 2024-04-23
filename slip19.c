#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd1, fd2;
    char buffer[256];
    const char* message = "Hello, world!\n";

    // Open a file for writing
    fd1 = open("shared_offset.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write a message to the file
    if (write(fd1, message, strlen(message)) == -1) {
        perror("write");
        close(fd1);
        exit(EXIT_FAILURE);
    }


    // Duplicate the file descriptor
    fd2 = dup(fd1);
    if (fd2 == -1) {
        perror("dup");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    // Move the file offset for fd1
    if (lseek(fd1, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // Read from fd1
    printf("Contents read from fd1:\n");
    ssize_t bytes_read;
    while ((bytes_read = read(fd1, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    if (bytes_read == -1) {
        perror("read");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // Move the file offset for fd2
    if (lseek(fd2, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // Read from fd2
    printf("\nContents read from fd2:\n");
    while ((bytes_read = read(fd2, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    if (bytes_read == -1) {
        perror("read");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // Close the file descriptors
    close(fd1);
    close(fd2);

    return 0;
}
