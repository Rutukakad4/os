#include <stdio.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output1.txt"

int main() {
    FILE *input_file, *output_file;
    int ch;
    int is_even = 1; // Flag to indicate whether the current character position is even or odd

    // Open the input file for reading
    input_file = fopen(INPUT_FILE, "r");
    if (input_file == NULL) {
        perror("fopen");
        return 1;
    }

    // Open the output file for writing
    output_file = fopen(OUTPUT_FILE, "w");
    if (output_file == NULL) {
        perror("fopen");
        fclose(input_file);
        return 1;
    }

    // Read characters from the input file and write alternate characters to the output file
    while ((ch = fgetc(input_file)) != EOF) {
        if (is_even) {
            fputc(ch, output_file);
        }
        is_even = !is_even; // Toggle the flag for alternate characters
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);

    printf("Alternate characters written to %s\n", OUTPUT_FILE);

    return 0;
}
