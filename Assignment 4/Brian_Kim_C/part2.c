#include <stdio.h>
#include <time.h>

#define MAX_CUPS_X 10 // Maximum number of cups of drink X
#define MAX_CUPS_Y 10 // Maximum number of cups of drink Y

// Function to solve the diet problem using brute force
void solveDietProblem() {
    clock_t start_time;
    start_time = clock();

    int minCupsX = 0, minCupsY = 0;
    double minCost = 9999999; // A large value to store the minimum cost

    for (int cupsX = 0; cupsX <= MAX_CUPS_X; cupsX++) {
        for (int cupsY = 0; cupsY <= MAX_CUPS_Y; cupsY++) {
            // Calculate total calories, vitamin A, and vitamin C from the drinks
            int totalCalories = cupsX * 60 + cupsY * 60;
            int totalVitaminA = cupsX * 12 + cupsY * 6;
            int totalVitaminC = cupsX * 10 + cupsY * 30;

            // Check if the requirements are met
            if (totalCalories >= 300 && totalVitaminA >= 36 && totalVitaminC >= 90) {
                double cost = cupsX * 0.12 + cupsY * 0.15; // Calculate cost

                // Update if the cost is minimized
                if (cost < minCost) {
                    minCost = cost;
                    minCupsX = cupsX;
                    minCupsY = cupsY;
                }
            }
        }
    }

    // Print the results
    printf("Minimum cost: $%.2f\n", minCost);
    printf("Number of cups of drink X: %d\n", minCupsX);
    printf("Number of cups of drink Y: %d\n", minCupsY);

    clock_t end_time = clock();
    double runtime = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Running time: %f seconds\n", runtime);
}

int main() {
    solveDietProblem(); // Solve the diet problem
    return 0;
}