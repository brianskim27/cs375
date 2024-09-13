#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<vector<int>> createRandomGraph(int n) {
    srand(time(nullptr));

    vector<vector<int>> adjList(n);

    for(int i = 0; i < n; ++i) {
        int numEdges = rand() % (n + 1);

        for(int j = 0; j < numEdges; ++j) {
            int dest = rand() % n;
            adjList[i].push_back(dest);
        }
    }
    return adjList;
}