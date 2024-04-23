#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size_in_bytes>\n", argv[0]);
        return 1;
    }

    long long n = atoll(argv[1]); // Convert string to long long

    DIR *dir;
    struct dirent *entry;
    struct stat filestat;

    // Open current directory
    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Get file info
        if (stat(entry->d_name, &filestat) == -1) {
            perror("stat");
            continue;
        }

        // Check if it's a regular file and its size is greater than n bytes
        if (S_ISREG(filestat.st_mode) && filestat.st_size > n) {
            printf("%s\n", entry->d_name);
        }
    }

    // Close directory
    closedir(dir);

    return 0;
}
