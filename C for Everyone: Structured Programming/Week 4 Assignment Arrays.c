#include <stdio.h>
#include <stdlib.h>

int main() {
    // Declare file pointers
    FILE *inputFile, *outputFile;
    int size, i, max;
    double sum = 0.0, average;

    // Open the input file for reading
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return 1;
    }

    // Read the first integer from the file, which tells how many integers to read
    fscanf(inputFile, "%d", &size);

    // Dynamically allocate memory for the array based on the size
    int *data = (int *)malloc(size * sizeof(int));
    if (data == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    // Read the remaining integers into the array
    for (i = 0; i < size; i++) {
        fscanf(inputFile, "%d", &data[i]);
        sum += data[i];  // Sum the values for calculating the average later
    }

    // Close the input file after reading
    fclose(inputFile);

    // Compute the average
    average = sum / size;

    // Find the maximum value
    max = data[0];
    for (i = 1; i < size; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }

    // Open the output file for writing
    outputFile = fopen("answer-hw3.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Unable to open output file for writing.\n");
        free(data);  // Free the allocated memory before exiting
        return 1;
    }

    // Print the results to the screen and to the output file
    printf("Array size: %d\n", size);
    printf("Array values: ");
    for (i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\nAverage: %.2f\n", average);
    printf("Max value: %d\n", max);

    fprintf(outputFile, "Array size: %d\n", size);
    fprintf(outputFile, "Array values: ");
    for (i = 0; i < size; i++) {
        fprintf(outputFile, "%d ", data[i]);
    }
    fprintf(outputFile, "\nAverage: %.2f\n", average);
    fprintf(outputFile, "Max value: %d\n", max);

    // Close the output file
    fclose(outputFile);

    // Free the allocated memory
    free(data);

    return 0;
}
