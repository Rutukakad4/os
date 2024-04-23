#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

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

    printf("Filename\tInode\t\tLinks\t\tSize\n");
    // Iterate over each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip special directories "." and ".."
        if (entry->d_name[0] == '.')
            continue;

        // Get file statistics
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        // Print filename, inode number, number of links, and size
        printf("%-15s\t%-10ld\t%-10ld\t%-10ld\n", entry->d_name, 
            (long)file_stat.st_ino, (long)file_stat.st_nlink, (long)file_stat.st_size);
    }

    closedir(dir);
    return 0;
}
