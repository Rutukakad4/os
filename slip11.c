#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename1> [<filename2> ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        struct stat file_stat;

        // Call stat() to get information about the file
        if (stat(argv[i], &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Determine the type of file
        if (S_ISREG(file_stat.st_mode)) {
            printf("%s: Regular file\n", argv[i]);
        } else if (S_ISDIR(file_stat.st_mode)) {
            printf("%s: Directory\n", argv[i]);
        } else if (S_ISCHR(file_stat.st_mode)) {
            printf("%s: Character device\n", argv[i]);
        } else if (S_ISBLK(file_stat.st_mode)) {
            printf("%s: Block device\n", argv[i]);
        } else if (S_ISFIFO(file_stat.st_mode)) {
            printf("%s: FIFO or pipe\n", argv[i]);
        } else if (S_ISLNK(file_stat.st_mode)) {
            printf("%s: Symbolic link\n", argv[i]);
        } else if (S_ISSOCK(file_stat.st_mode)) {
            printf("%s: Socket\n", argv[i]);
        } else {
            printf("%s: Unknown file type\n", argv[i]);
        }
    }

    return 0;
}
