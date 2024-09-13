#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PHOTOS 20
#define NUM_CATEGORIES 3

// Structure to represent an edge between photos with similarity as weight
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for Union-Find
struct Subset {
    int parent, rank;
};

// Function to find the parent of a node (with path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Function to perform union of two sets (with union by rank)
void unionSet(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to compare edges based on weight for sorting
int compare(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeB->weight - edgeA->weight; // Sort in non-increasing order of weight
}

// Function to classify photos into disjoint subsets
void classifyPhotos(int similarities[NUM_PHOTOS][NUM_PHOTOS], FILE *outputFile) {
    struct Edge edges[NUM_PHOTOS * NUM_PHOTOS];
    int edgeCount = 0;

    // Store all edges in an array
    for (int i = 0; i < NUM_PHOTOS; i++) {
        for (int j = i + 1; j < NUM_PHOTOS; j++) {
            edges[edgeCount].src = i;
            edges[edgeCount].dest = j;
            edges[edgeCount].weight = similarities[i][j];
            edgeCount++;
        }
    }

    // Sort edges in non-increasing order of similarity
    qsort(edges, edgeCount, sizeof(struct Edge), compare);

    struct Subset subsets[NUM_PHOTOS];
    for (int i = 0; i < NUM_PHOTOS; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int categories[NUM_CATEGORIES] = {0};

    // Process edges to form disjoint subsets (maximum spanning trees)
    for (int i = 0; i < edgeCount; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int srcParent = find(subsets, src);
        int destParent = find(subsets, dest);

        if (srcParent != destParent) {
            unionSet(subsets, srcParent, destParent);
            categories[srcParent % NUM_CATEGORIES]++;
        }
    }

    // Output the number of photos in each subset to the output file
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        fprintf(outputFile, "Category %d: Number of photos = %d\n", i + 1, categories[i]);
    }
}

int main() {
    clock_t start_time = clock(); // Start measuring time
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    int similarities[NUM_PHOTOS][NUM_PHOTOS] = {0};

    // Read similarity values from the input file
    int p1, p2, similarity;
    char discard[50];
    while (fscanf(inputFile, "%[^0-9]%d%[^0-9]%d%[^0-9]%d%[^0-9]", discard, &p1, discard, &p2, discard, &similarity, discard) != EOF) {
        similarities[p1 - 1][p2 - 1] = similarity; // Adjust indices to start from 0
        similarities[p2 - 1][p1 - 1] = similarity; // Similarity matrix is symmetric
        fscanf(inputFile, "%*[^\n]"); // Discard rest of the line
    }

    classifyPhotos(similarities, outputFile);


    clock_t end_time = clock(); // End measuring time
    double runtime = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(outputFile, "Running time: %lf seconds\n", runtime);

    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}