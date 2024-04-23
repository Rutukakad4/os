/*#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include<string.h>

#define START_DATE 1711929600//1622365200 // Timestamp for 1st May 2023 00:00:00 UTC
#define END_DATE   1721080000 // Timestamp for 15th May 2023 23:59:59 UTC

void print_files_created_between(const char *directory, time_t start_date, time_t end_date) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_info;
    char filepath[256];

    // Open directory
    dir = opendir(directory);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Iterate through directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Construct full path to file
        snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

        // Get file information
        if (stat(filepath, &file_info) == -1) {
            perror("stat");
            continue;
        }

        // Check if the file creation time is within the specified range
        if (file_info.st_mtime >= start_date && file_info.st_mtime <= end_date) {
            printf("File: %s, Inode: %lu\n", entry->d_name, file_info.st_ino);
        }
    }

    // Close directory
    closedir(dir);
}

int main() {
    // Specify the directory you want to search
    const char *directory = ".";

    // Print files created between 1st May 2023 and 15th May 2023
    printf("Files created between 1st May 2023 and 15th May 2023:\n");
    print_files_created_between(directory, START_DATE, END_DATE);

    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

// Function to check if a file was created between specified dates
int is_created_between(const char *filename, const time_t start_date, const time_t end_date) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        return 0;
    }
    time_t creation_time = file_stat.st_ctime;
    return (creation_time >= start_date && creation_time <= end_date);
}

// Function to print the names of files created between specified dates
void print_files_created_between(const char *dir_path, const time_t start_date, const time_t end_date) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);
            if (is_created_between(filepath, start_date, end_date)) {
                struct stat file_stat;
                if (stat(filepath, &file_stat) == -1) {
                    perror("stat");
                    continue;
                }
                printf("File: %-20s Inode: %ld\n", entry->d_name, (long)file_stat.st_ino);
            }
        }
    }
    closedir(dir);
}

int main() {
    // Dates for comparison
    struct tm start_date = {0};  // 1st May 2023
    start_date.tm_year = 2024 - 1900;
    start_date.tm_mon = 3;
    start_date.tm_mday = 1;
    start_date.tm_hour = 0;
    start_date.tm_min = 0;
    start_date.tm_sec = 0;

    struct tm end_date = {0};    // 15th May 2023
    end_date.tm_year = 2024 - 1900;
    end_date.tm_mon = 3;
    end_date.tm_mday = 15;
    end_date.tm_hour = 23;
    end_date.tm_min = 59;
    end_date.tm_sec = 59;

    time_t start_time = mktime(&start_date);
    time_t end_time = mktime(&end_date);

    // Directory to search for files
    const char *dir_path = ".";

    // Print files created between specified dates
    printf("Files created between 1st May 2023 and 15th May 2023:\n");
    print_files_created_between(dir_path, start_time, end_time);

    return 0;
}

