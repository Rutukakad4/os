#include <stdio.h>
#include <stdlib.h>

// User-defined functions
void cleanup1() {
    printf("Cleanup function 1\n");
}

void cleanup2() {
    printf("Cleanup function 2\n");
}

int main() {
    // Registering cleanup1 with atexit
    if (atexit(cleanup1) != 0) {
        fprintf(stderr, "Failed to register cleanup1\n");
        return 1;
    }

    // Registering cleanup2 with atexit
    if (atexit(cleanup2) != 0) {
        fprintf(stderr, "Failed to register cleanup2\n");
        return 1;
    }

    // Registering cleanup1 again with atexit
    if (atexit(cleanup1) != 0) {
        fprintf(stderr, "Failed to register cleanup1\n");
        return 1;
    }

    printf("Main function\n");

    return 0;
}
