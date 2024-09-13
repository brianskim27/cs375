#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <utility>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

struct Node {
    int id;
    vector<pair<int, double>> neighbors;
};

class Graph {
public:
    Graph(int vertices);
    void addEdge(int from, int to, int weight);
    void printGraph();

private:
    
};

#endif // GRAPH_H