#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Iterate over each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        char *filename = entry->d_name;

        // Skip special directories "." and ".."
        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0)
            continue;

        // Get file statistics
        if (stat(filename, &file_stat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        // Check if the file is a regular file and the user has write permission
        if (S_ISREG(file_stat.st_mode) && (file_stat.st_mode & S_IWUSR)) {
            printf("%s\n", filename);
        }
    }

    closedir(dir);
    return 0;
}
