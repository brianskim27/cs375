#include <iostream>
#include <chrono>
#include <iomanip>

//#include "test.h"
#include "bellmanFord.h"
#include "aStar.h"
#include "graph.h"
// #include "random-graph.cpp"
using namespace std;

struct GraphData {
    vector<Node> nodes; // A*
    vector<Edge> edges; // Bellman-Ford
};

vector<Node> createGraph(int numRows, int numCols, double defaultCost = 1.0) {
    int numNodes = numRows * numCols;
    vector<Node> graph(numNodes);

    for (int i = 0; i < numNodes; ++i) {
        graph[i].id = i;
        int row = i / numCols;
        int col = i % numCols;

        // Connect to the left neighbor
        if (col > 0) {
            int leftNeighbor = i - 1;
            graph[i].neighbors.push_back(make_pair(leftNeighbor, defaultCost));
        }

        // Connect to the right neighbor
        if (col < numCols - 1) {
            int rightNeighbor = i + 1;
            graph[i].neighbors.push_back(make_pair(rightNeighbor, defaultCost));
        }

        // Connect to the top neighbor
        if (row > 0) {
            int topNeighbor = i - numCols;
            graph[i].neighbors.push_back(make_pair(topNeighbor, defaultCost));
        }

        // Connect to the bottom neighbor
        if (row < numRows - 1) {
            int bottomNeighbor = i + numCols;
            graph[i].neighbors.push_back(make_pair(bottomNeighbor, defaultCost));
        }
    }

    return graph;
}


vector<Node> createRandomGraph(int n) {
    int maxDegree = 2;
    vector<Node> graph(n);

    srand(time(nullptr));

    for (int i = 0; i < n; ++i) {
        graph[i].id = i;
        int numConnections = rand() % maxDegree + 1;
        for(int j = 0; j < numConnections; ++j) {
            int neighborId = rand() % n;

            if(i != neighborId && find_if(graph[i].neighbors.begin(), graph[i].neighbors.end(), [neighborId](const pair<int, double>& p) { return p.first == neighborId; }) == graph[i].neighbors.end()) {
                bool isNegative = rand() % 4 == 0; // 25% chance of being negative
                double weight = rand() %  100 + 1;
                if (isNegative) {
                    weight = -weight; // Make the weight negative
                }
                graph[i].neighbors.push_back(make_pair(neighborId, weight));
            }
        }
    }
    return graph;
}

/*
GraphData createRandomGraph(int numNodes, int numEdges) {
    GraphData graphData;
    graphData.nodes.resize(numNodes);

    srand(time(nullptr));

    // Populate edges
    while (graphData.edges.size() < numEdges) {
        int from = rand() % numNodes;
        int to = rand() % numNodes;

        // Avoid self-loops and ensure limited number of outgoing connections
        if (from != to && graphData.nodes[from].neighbors.size() < 10) {
            double weight = rand() % 100 + 1;  // Random weight between 1 and 100

            // Add to Node structure for A*
            graphData.nodes[from].neighbors.push_back(std::make_pair(to, weight));

            // Add to Edge structure for Bellman-Ford
            Edge edge = {from, to, static_cast<int>(weight)};
            graphData.edges.push_back(edge);
        }
    }

    return graphData;
}
*/


void printGraph(const vector<Node>& graph) {
    for(const Node& node : graph) {
        cout << "Node " << node.id << " connects to: ";
        for(const auto& neighbor : node.neighbors) {
            cout << "[Node " << neighbor.first << ", Weight: " << neighbor.second << "] ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[]) {
    /* Bellman-Ford Algorithm */

    // create random graph
    int numNodes = 100;
    vector<Node> randomGraph = createRandomGraph(numNodes);
    int fromV = 5;
    int toV = 99;
    printGraph(randomGraph);

    std::cout << "\nShortest path from " << fromV << " to " << toV << ":\n";
    std::cout << "\n***** Bellman-Ford Algorithm test *****\n";
    // start runtime
    auto start1 = std::chrono::high_resolution_clock::now();

    // int V = 5; // Number of vertices in graph
    // int E = 8; // Number of edges in graph
    
    // initialize graph
    BellmanFord graph(randomGraph);
 
    std::vector<int> shortestDistances = graph.shortestPath(fromV);

    if (shortestDistances.empty()) std::cout << "Graph contains negative weight cycle!\n";
    else {
        std::cout << "Shortest distances from vertex " << fromV << " to other vertices:\n";
        for (int i = 0; i < numNodes; ++i) {
            std::cout << "Vertex " << i << ": ";
            if (shortestDistances[i] == std::numeric_limits<int>::max()) std::cout << "INF\n";  // path from source to destination does not exist
            else std::cout << shortestDistances[i] << "\n"; // shortest distance from source to destination
        }
    }

    //end runtime
    auto end1 = std::chrono::high_resolution_clock::now();
    
    //calculate runtime
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << "Runtime (Bellman-Ford): " << duration1.count() << " seconds" << std::endl;

    /* A* Algorithm */
    std::cout << "\n***** A* Algorithm test ******\n";

    // start runtime
    auto start2 = std::chrono::high_resolution_clock::now();   

    
    int result = AStar(randomGraph, fromV, toV);
    if(result != -1) {
        cout << "Shortest path from " << fromV << " to " << toV << " is " << result << " length" << endl;
    }

    //end runtime
    auto end2 = std::chrono::high_resolution_clock::now();
    
    //calculate runtime
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << "Runtime (A*): " << duration2.count() << " seconds" << std::endl;

    return 0;
}