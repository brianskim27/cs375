#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <vector>
#include <limits>

#include "graph.h"
using namespace std;

/*
struct Edge {
    int from, to, weight;
};
*/

class BellmanFord {
    public:
        BellmanFord(const vector<Node>& graph) : graph(graph) {}
        vector<int> shortestPath(int source);
    private:
        vector<Node> graph;
};

/*
class BellmanFord {
public:
    BellmanFord(int vertices, int edges);
    void addEdge(int from, int to, int weight);
    std::vector<int> shortestPath(int from);

private:
    int V, E;
    std::vector<Edge> edges;
};
*/

#endif //BELLMANFORD_H