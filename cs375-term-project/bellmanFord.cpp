#include <iostream>
#include <vector>
#include <limits>

#include "bellmanFord.h"
#include "graph.h"
using namespace std;

std::vector<int> BellmanFord::shortestPath(int source) {
    int V = graph.size();
    std::vector<int> distance(V, std::numeric_limits<int>::max());
    distance[source] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < V; j++) {
            for (const auto& neighbor : graph[j].neighbors) {
                int u = j;
                int v = neighbor.first;
                int weight = neighbor.second;
                if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < V; j++) {
        for (const auto& neighbor : graph[j].neighbors) {
            int u = j;
            int v = neighbor.first;
            int weight = neighbor.second;
            if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                // Negative cycle found
                return std::vector<int>(); // Returning an empty vector as a signal
            }
        }
    }

    return distance;
}


/*
BellmanFord::BellmanFord(int vertices, int edges) : V(vertices), E(edges) {}

void BellmanFord::addEdge(int from, int to, int weight) {
    Edge edge = {from, to, weight};
    edges.push_back(edge);
}

std::vector<int> BellmanFord::shortestPath(int source) {
    std::vector<int> distance(V, std::numeric_limits<int>::max());
    distance[source] = 0;

    // Relax all edges V-1 times
    for(int i = 0; i < V - 1; i++) {
        for(const auto& edge : edges) {
            int f = edge.from;
            int t = edge.to;
            int w = edge.weight;
            if(distance[f] != std::numeric_limits<int>::max() && distance[f] + w < distance[t]) {
                distance[t] = distance[f] + w;
            }
        }
    }

    // Check for negative weight cycles (total sum of edge weights around the cycle is negative)
    for(const auto& edge : edges) {
        int f = edge.from;
        int t = edge.to;
        int w = edge.weight;
        if(distance[f] != std::numeric_limits<int>::max() && distance[f] + w < distance[t]) {
            // Negative cycle found, return an empty vector indicating no shortest paths
            return std::vector<int>();
        }
    }

    return distance;
}
*/