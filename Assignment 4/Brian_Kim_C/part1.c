#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_COURSES 100

// Function to calculate the minimum number of semesters
int calculateMinSemesters(int n, int graph[MAX_COURSES][MAX_COURSES], int indegree[MAX_COURSES]) {
    int semesters = 0;
    int completedCourses = 0;
    int queue[MAX_COURSES];
    int front = 0;
    int rear = 0;

    // Enqueue all courses with no prerequisites
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front != rear) {
        int currentCourse = queue[front++];
        completedCourses++;

        // Decrement the indegree of all courses dependent on the current course
        for (int i = 0; i < n; i++) {
            if (graph[currentCourse][i] == 1) {
                indegree[i]--;
                if (indegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }

        // Increment the number of semesters if all prerequisites of a course are completed
        if (completedCourses % 5 == 0) {
            semesters++;
        }
    }

    return semesters;
}

int main() {
    int n = 15; // Number of courses
    int graph[MAX_COURSES][MAX_COURSES] = {0}; // Adjacency matrix representation of the graph
    int indegree[MAX_COURSES] = {0}; // Array to store the indegree of each course

    // Set the prerequisites for each course
    graph[3][1] = 1; // cs4 requires cs2
    graph[4][3] = 1; // cs5 requires cs4
    graph[5][0] = 1; // cs6 requires cs1
    graph[5][2] = 1; // cs6 requires cs3
    graph[6][3] = 1; // cs7 requires cs4
    graph[7][4] = 1; // cs8 requires cs5
    graph[7][5] = 1; // cs8 requires cs6
    graph[8][6] = 1; // cs9 requires cs7
    graph[9][8] = 1; // cs10 requires cs9
    graph[10][7] = 1; // cs11 requires cs8
    graph[11][2] = 1; // cs12 requires cs3
    graph[12][0] = 1; // cs13 requires cs1
    graph[12][2] = 1; // cs13 requires cs3
    graph[13][3] = 1; // cs14 requires cs4
    graph[13][5] = 1; // cs14 requires cs6
    graph[14][13] = 1; // cs15 requires cs14

    clock_t start = clock(); // Start measuring time
    
    // Calculate the indegree of each course
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[j][i] == 1) {
                indegree[i]++;
            }
        }
    }

    // Calculate the minimum number of semesters
    int minSemesters = calculateMinSemesters(n, graph, indegree);

    printf("Minimum number of semesters: %d\n", minSemesters);
    
    clock_t end = clock(); // Stop measuring time
    double runtime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Running time: %lf seconds\n", runtime);

    return 0;
}