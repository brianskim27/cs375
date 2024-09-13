#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void generateRandomGraph(Graph &g, WeightMap &weight_map, int num_nodes, int num_edges) {
    mt19937 rng;
    generate_random_graph(g, num_nodes, num_edges, rng, true, true);

    // Generate random weights for edges
    for (auto e : make_iterator_range(edges(g))) {
        put(weight_map, e, rand() % 10 + 1); // Assigning random weights (1 to 10)
    }
}

void bellmanFordShortestPath(const Graph &g, WeightMap &weight_map, int source) {
    vector<int> distances(num_vertices(g), numeric_limits<int>::max());
    distances[source] = 0;

    for (int i = 0; i < num_vertices(g) - 1; ++i) {
        for (auto e : make_iterator_range(edges(g))) {
            Vertex u = source(e, g);
            Vertex v = target(e, g);
            if (distances[u] != numeric_limits<int>::max() &&
                distances[v] > distances[u] + get(weight_map, e)) {
                distances[v] = distances[u] + get(weight_map, e);
            }
        }
    }

    // Display shortest path distances
    cout << "Bellman-Ford Shortest Path Distances from source " << source << ":\n";
    for (int i = 0; i < num_vertices(g); ++i) {
        cout << "Vertex " << i << ": " << distances[i] << "\n";
    }
}

void aStarShortestPath(const Graph &g, WeightMap &weight_map, int source, int target) {
    vector<Vertex> predecessors(num_vertices(g));
    vector<int> distances(num_vertices(g));
    vector<bool> visited(num_vertices(g), false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source));
    distances[source] = 0;

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == target) break;

        if (!visited[u]) {
            visited[u] = true;
            graph_traits<Graph>::out_edge_iterator ei, ei_end;
            for (tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei) {
                int v = target(*ei, g);
                int weight = get(weight_map, *ei);
                int new_dist = dist + weight;
                if (new_dist < distances[v]) {
                    distances[v] = new_dist;
                    predecessors[v] = u;
                    pq.push(make_pair(new_dist, v));
                }
            }
        }
    }

    // Display shortest path distances
    cout << "\nA* Shortest Path Distances from source " << source << " to target " << target << ":\n";
    for (int i = 0; i < num_vertices(g); ++i) {
        cout << "Vertex " << i << ": " << distances[i] << "\n";
    }
}

int main() {
    int num_nodes = 6;
    int num_edges = 8;

    Graph g(num_nodes);
    WeightMap weight_map = get(edge_weight, g);

    generateRandomGraph(g, weight_map, num_nodes, num_edges);

    // Source and target vertices for shortest path calculation
    int source = 0;
    int target = 5;

    // Run Bellman-Ford algorithm
    bellmanFordShortestPath(g, weight_map, source);

    // Run A* algorithm
    aStarShortestPath(g, weight_map, source, target);

    return 0;
}