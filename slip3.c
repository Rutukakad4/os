#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    //char *filename = argv[1];
    struct stat file_stat;
    fd=open(argv[1],O_RDONLY);
    // Use fstat to get file properties
    if (fstat(fd, &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    // Print file properties
    printf("File: %s\n", argv[1]);
    printf("Inode number: %ld\n", file_stat.st_ino);
    printf("Number of hard links: %ld\n", file_stat.st_nlink);
    printf("File permissions: ");
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    printf("File size: %ld bytes\n", file_stat.st_size);

    return 0;
}
