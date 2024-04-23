#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILENAME "holed_file.txt"
#define BUFFER_SIZE 256

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    const char* data1 = "This is data1.";
    const char* data2 = "This is data2.";

    // Create a new file or truncate an existing one
    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write data1 to the file
    if (write(fd, data1, strlen(data1)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Create a hole in the file
    if (lseek(fd, 1024, SEEK_CUR) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write data2 after the hole
    if (write(fd, data2, strlen(data2)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    close(fd);

    // Open the file for reading
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read and display the contents of the file
    printf("Contents of the file:\n");
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    close(fd);

    return 0;
}
