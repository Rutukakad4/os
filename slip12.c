#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open file1.txt for reading
    FILE *file1 = fopen("file1.txt", "r");
    if (file1 == NULL) {
        perror("Error opening file1.txt");
        return 1;
    }

    // Open file2.txt for writing
    FILE *file2 = fopen("file2.txt", "w");
    if (file2 == NULL) {
        perror("Error opening file2.txt");
        fclose(file1);
        return 1;
    }

    // Read content of file1.txt and write it to file2.txt
    int ch;
    while ((ch = fgetc(file1)) != EOF) {
        fputc(ch, file2);
    }

    // Close both files
    fclose(file1);
    fclose(file2);

    // Remove file1.txt
    if (remove("file1.txt") != 0) {
        perror("Error removing file1.txt");
        return 1;
    }

    // Rename file2.txt to file1.txt
    if (rename("file2.txt", "file1.txt") != 0) {
        perror("Error renaming file2.txt to file1.txt");
        return 1;
    }

    printf("Content of file1.txt moved to file2.txt, file1.txt removed, and file2.txt renamed to file1.txt successfully.\n");

    return 0;
}
