#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
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

    printf("Subdirectories in the current directory:\n");

    // Iterate over each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip special directories "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Get file statistics
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        // Check if the entry is a directory
        if (S_ISDIR(file_stat.st_mode)) {
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
