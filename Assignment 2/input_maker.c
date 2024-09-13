#include <stdio.h>

// Define a structure for point
struct Point {
    int x;
    int y;
};

int main() {
    int n = 10000;
    struct Point p[n];

    // Fill the array p with data
    for (int i = 0; i < n; i++) {
        p[i].x = i * i;
        p[i].y = i * i;
    }

    // Open a file for writing
    FILE *file = fopen("input.txt", "w");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Unable to open file.\n");
        return 1; // Exit with an error code
    }

    // Write the data to the file in the desired format
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d %d\n", p[i].x, p[i].y);
    }

    // Close the file
    fclose(file);

    printf("Data written to input.txt\n");

    return 0;
}