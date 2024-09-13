#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

// Define a structure to represent a 2D point with x and y coordinates
struct Point {
    int x, y;
};

// Define a structure that stores the indices of the pair of points with the minimum distance between them
struct ClosestPairIndices {
    int i, j;
};

// Compute the Euclidean distance between two points
double calcEuclideanDistance(struct Point p1, struct Point p2) {
    return sqrt((double)((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

// Sort the points by x and y coordinates
int compareX(const void *a, const void *b) {
    return ((struct Point *)a)->x - ((struct Point *)b)->x;
}
int compareY(const void *a, const void *b) {
    return ((struct Point *)a)->y - ((struct Point *)b)->y;
}

// Return the min of two values
double min(double a, double b) {
    return (a < b) ? a : b;
}

// Find closest pair of points in a strip of points sorted by the y coordinate
double stripClosestPair(struct Point strip[], int size, double d) {
    double minDistance = d;
    struct ClosestPairIndices closestIndices = {-1, -1};

    // Sort by the y coordinate
    qsort(strip, size, sizeof(struct Point), compareY);

    // Iterate through the strip to find the closest pair of points
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDistance; j++) {
            double distance = calcEuclideanDistance(strip[i], strip[j]);
            if (distance < minDistance) {
                minDistance = distance;
                // Store the indices of the pair of points with the minimum distance between them
                closestIndices.i = i;
                closestIndices.j = j;
            }
        }
    }
    return minDistance;
}

// Find closest pair of points in the array using divide & conquer
double closestPair(struct Point points[], int n, struct ClosestPairIndices *closestIndices) {
    // If there are 3 or less points, use brute-force approach
    if (n <= 3) {
        double minDistance = DBL_MAX;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double distance = calcEuclideanDistance(points[i], points[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    // Store the indices of the pair of points with the minimum distance between them
                    closestIndices->i = i;
                    closestIndices->j = j;
                }
            }
        }

        return minDistance;
    }

    // Sort by the x coordinate
    qsort(points, n, sizeof(struct Point), compareX);

    // Find the middle point
    int mid = n / 2;
    struct Point midPoint = points[mid];

    // Find closest pairs in left and right halves
    struct ClosestPairIndices leftIndices, rightIndices;
    double leftDistance = closestPair(points, mid, &leftIndices);
    double rightDistance = closestPair(points + mid, n - mid, &rightIndices);

    // Find min distance between left and right halves
    double minDistance = min(leftDistance, rightDistance);

    // Find side with the closest pair
    if (minDistance == leftDistance) {
        *closestIndices = leftIndices;
    } 
    else {
        closestIndices->i = rightIndices.i + mid;
        closestIndices->j = rightIndices.j + mid;
    }

    // Create a strip of points within min distance of the middle line
    struct Point strip[n];
    int j = 0;

    for (int i = 0; i < n; i++) {
        if (abs(points[i].x - midPoint.x) < minDistance) {
            strip[j] = points[i];
            j++;
        }
    }

    // Find min distance within strip
    double stripDistance = stripClosestPair(strip, j, minDistance);

    // Check if strip distance is less than min distance and update ClosestIndices if so
    if (stripDistance < minDistance) {
        closestIndices->i = strip[closestIndices->i].x < strip[closestIndices->j].x ? closestIndices->i : closestIndices->j;
        closestIndices->j = strip[closestIndices->i].x < strip[closestIndices->j].x ? closestIndices->j : closestIndices->i;
        return stripDistance;
    }

    return minDistance;
}

double bruteForceClosestPair(struct Point points[], int n, struct ClosestPairIndices *closestIndices) {
    double minDistance = DBL_MAX;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double distance = calcEuclideanDistance(points[i], points[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndices->i = i;
                closestIndices->j = j;
            }
        }
    }

    return minDistance;
}

int main(int argc, char* argv[]) {
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

/* Part 1: Outputting the minimum distance between P[i] and P[j], as well as indices i and j */

    struct Point points[20000]; // Set maximum number of points to 20,000
    int n = 0;

    // Read all the points in the input file
    while (fscanf(inputFile, "%d %d", &points[n].x, &points[n].y) == 2) {
        n++;
    }

    struct ClosestPairIndices closestIndices = {-1, -1};
    double closestDistance = closestPair(points, n, &closestIndices);

    // Print i and j for P[i] and P[j] (minimum distance found between them) and the minimum distance in the output file
    if (closestIndices.i != -1 && closestIndices.j != -1) {
        fprintf(outputFile, "%d %d ", closestIndices.i, closestIndices.j);
    }
    fprintf(outputFile, "%lf\n", closestDistance);

/* Part 2: Comparing the time complexity between divide & conquer and brute-force and printing the time costs */

    // Divide & Conquer
    clock_t start = clock();
    struct ClosestPairIndices closestIndicesDC = {-1, -1};
    double closestDistanceDC = closestPair(points, n, &closestIndicesDC);
    clock_t end = clock();
    double executionTimeDC = (double)(end - start) / CLOCKS_PER_SEC;

    // Brute-force
    start = clock();
    struct ClosestPairIndices closestIndicesBF = {-1, -1};
    double closestDistanceBF = bruteForceClosestPair(points, n, &closestIndicesBF);
    end = clock();
    double executionTimeBF = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the results for Divide & Conquer
    printf("Divide & Conquer\n");
    if (closestIndicesDC.i != -1 && closestIndicesDC.j != -1) {
        printf("i = %d j = %d D = %lf\n", closestIndicesDC.i, closestIndicesDC.j, closestDistanceDC);
    }
    printf("Execution Time: %lf seconds\n", executionTimeDC);
    // Print the results for Brute Force
    printf("Brute Force\n");
    if (closestIndicesBF.i != -1 && closestIndicesBF.j != -1) {
        printf("i = %d j = %d D = %lf\n", closestIndicesBF.i, closestIndicesBF.j, closestDistanceBF);
    }
    printf("Execution Time: %lf seconds\n", executionTimeBF);
    
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}