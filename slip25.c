#include <stdio.h>
#include <stdlib.h>

void cleanup_files() {
    printf("Doing cleanup work, closing files...\n");
    // Perform cleanup related to closing files
}

void cleanup_memory() {
    printf("Doing cleanup work, freeing memory...\n");
    // Perform cleanup related to freeing memory
}

int main() {
    // Register cleanup functions
    if (atexit(cleanup_files) != 0) {
        fprintf(stderr, "Failed to register cleanup_files\n");
        return 1;
    }

    if (atexit(cleanup_memory) != 0) {
        fprintf(stderr, "Failed to register cleanup_memory\n");
        return 1;
    }

    // Main program logic
    printf("Hello");
    printf("Welcome to os");

    // Terminate the program
    return 0;
}
