#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10000   // Maximum # of keys allowed in the array

int hashMap[MAX] = {0};
int pair1[MAX] = {0};
int pair2[MAX] = {0};

int main(int argc, char *argv[]) {
    // If there are no three args, print error and exit the program
    if(argc != 3) {
        printf("Usage: progname <input_file> <output_file>");
        exit(0);
    }

    // Open the input file and the output file
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    //If there is no input file, then print error and exit the program
    if(!inputFile) {
        perror("Error opening input file.\n");
        exit(0);
    }

    // If there is no output file, then print error and exit the program
    if(!outputFile) {
        perror("Error opening output file.\n");
        exit(0);
    }

    int arr[MAX];
    int n = 0;
    int temp;

    // Reading the keys in the input file into an array
    while (fscanf(inputFile, "%d", &temp) != EOF) {
        arr[n++] = temp;
    }
    
    // Calculate the absolute difference between each pair of keys in the array
    for (int i = 0; i < n; i++) {   // Outer loop
        for (int j = i + 1; j < n; j++) {   // Inner loop
            int diff = abs(arr[i] - arr[j]);   
            hashMap[diff] = 1;
            
            // Store the larger difference first
            if (arr[i] > arr[j]) {
                pair1[diff] = arr[i];
                pair2[diff] = arr[j];
            } 
            else {
                pair1[diff] = arr[j];
                pair2[diff] = arr[i];
            }
        }
    }

    bool match = false;

    // Iterate through the array again to find any matches
    for (int i = 0; i < n; i++) {   
        if (hashMap[arr[i]]) {
            fprintf(outputFile, "%d %d %d\n", arr[i], pair1[arr[i]], pair2[arr[i]]);    // If there is a match, in the output file, print the three keys (the last two in decreasing order) 
            match = true;
        }
    }

    if (!match) {
        fopen(argv[2], "w");    // Outputs a 0 byte blank file if there are no matching keys
    }
    
    // Close the input file and the output file and end the program
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}