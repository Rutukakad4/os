#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FILENAME "file_with_hole.txt"

int main() {
    // Create a file with a hole
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    char data1[] = "This is data before the hole.";
    char data2[] = "This is data after the hole.";
    if (write(fd, data1, sizeof(data1) - 1) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Create a hole in the file
    if (lseek(fd, 1024, SEEK_CUR) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    // Write more data to the file
    if (write(fd, data2, sizeof(data2) - 1) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Read the file and display the data read at the offsets corresponding to the hole
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read at offset corresponding to the hole
    char buffer[1024];
    int bytes_read = pread(fd, buffer, sizeof(buffer), 512);
    if (bytes_read == -1) {
        perror("pread");
        exit(EXIT_FAILURE);
    }

    printf("Data read at offset corresponding to the hole:\n");
    fwrite(buffer, 1, bytes_read, stdout);

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
