#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#define MAX_NODES 100

int N;
int graph[MAX_NODES][MAX_NODES];
int distance[MAX_NODES];
int parent[MAX_NODES];
bool visited[MAX_NODES];

// Function to find the minimum distance vertex that is not yet included in the shortest path tree
int minDistance() {
    int min = INT_MAX, min_index;
    for(int v = 1; v <= N; v++) {
        if(!visited[v] && distance[v] < min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the shortest path from first to last
void printPath(int last, FILE *output) {
    if(last == 0)
        return;

    printPath(parent[last], output);
    fprintf(output, "#%d ", last);
}

// Function to perform Dijkstra's algorithm
void dijkstra(int first) {
    for(int i = 1; i <= N; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[first] = 0;    // source has distance 0 from itself
    parent[first] = 0;  // source has no parent

    for(int count = 1; count <= N; count++) {
        int u = minDistance();
        visited[u] = true;

        for(int v = 1; v <= N; v++) {
            if(!visited[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];    // update shortest distance if path from source to 'v' through 'u' is shorter than current distance to 'v'
                parent[v] = u;  // path from source to 'v' goes through 'u'
            }
        }
    }
}

int main(int argc, char* argv[]) {
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // If there are no three args, print error and exit the program
    if(argc != 3) {
        printf("Usage: progname <input_file> <output_file>");
        exit(0);
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "r");

    //If there is no input file, then print error and exit the program
    if(!inputFile) {
        perror("Error opening input file.\n");
        exit(0);
    }

    // Read the number of nodes
    fscanf(inputFile, "%d", &N);

    // Initialize the graph
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            graph[i][j] = 0;
    }

    // Read the direct connections and distances
    int i, j, dij;
    while(fscanf(inputFile, "%d %d %d", &i, &j, &dij) != EOF) {
        graph[i][j] = dij;
        graph[j][i] = dij; // Assuming the graph is undirected
    }

    fclose(inputFile);

    // Get the first and last nodes
    int first, last;

    printf("Enter the first city: ");
    scanf("%d", &first);
    printf("Enter the last city: ");
    scanf("%d", &last);

    // Check for valid inputs
    if (first < 1 || first > N || last < 1 || last > N) {
        printf("Invalid first or last city.\n");
        return 1;
    }

    // Perform Dijkstra's algorithm from the first city
    dijkstra(first);

    // Open the output file
    FILE *outputFile = fopen(argv[2], "w");

    // If there is no output file, then print error and exit the program
    if(!outputFile) {
        perror("Error opening output file.\n");
        exit(0);
    }

    // Write the distance matrix
    fprintf(outputFile, "//** Final D table **//\n");
    for (int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++)
            fprintf(outputFile, "%d ", graph[i][j]);
        fprintf(outputFile, "\n");
    }

    // Write the parent matrix
    fprintf(outputFile, "\n//** Final P table **//\n");
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++)
            fprintf(outputFile, "%d ", parent[i] == 0 ? 0 : parent[i]);
        fprintf(outputFile, "\n");
    }

    // Print the shortest path from first node to last node
    fprintf(outputFile, "\n//** Path of the shortest distance from node #%d to node #%d **//\n", first, last);
    printPath(last, outputFile);

    // Print the shortest distance from first to last node
    fprintf(outputFile, "\n\n//** Shortest distance from node #%d to node #%d **//\n", first, last);
    fprintf(outputFile, "Distance: %d\n", distance[last]);

    // Measure running time
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long micros = end.tv_usec - start.tv_usec;
    double runningTime = seconds + micros / 1e6;

    fprintf(outputFile, "\n//** Running time **//\n");
    fprintf(outputFile, "Running time: %.6f seconds\n", runningTime);

    fclose(outputFile);
    return 0;
}