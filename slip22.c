#include <stdio.h>

#define FILENAME "example.txt"
#define BUFFER_SIZE 256

int main() {
    FILE *file;
    char buffer[BUFFER_SIZE];
    int count = 0;

    // Open the file for reading
    file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Read every 10th character from the file and print it
    while (!feof(file)) {
        int ch = fgetc(file);
        if (ch == EOF) {
            break;
        }
        if (count % 15 == 0) {
            putchar(ch);
        }
        count++;
    }

    // Close the file
    fclose(file);

    // Print the total number of characters printed
    printf("\nTotal characters printed: %d\n", count/15);

    return 0;
}
