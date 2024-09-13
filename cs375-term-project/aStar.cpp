#include "aStar.h"
// #include "random-graph.cpp"
#include "graph.h"
using namespace std;

bool isValid(int nodeId, const vector<Node>& graph) {
    return (nodeId >= 0) && (nodeId < graph.size());
}

bool isDest(int row, int col, Pair dest) {
    if(row == dest.first && col == dest.second)
        return true;
    else
        return false;
}

bool isDest(int nodeId, int destId) {
    return nodeId == destId;
}

double calculateHVal(int nodeId, int destId) {
    int dx = abs(nodeId % COL - destId % COL);
    int dy = abs(nodeId / COL - destId / COL);
    return dx + dy;
}

void tracePath(map<int, Cell> cellDetails, int destId) {
    cout << "Path: ";
    stack<int> Path;
    int temp_id = destId;

    while (cellDetails[temp_id].parent_id != temp_id) {
        Path.push(temp_id);
        temp_id = cellDetails[temp_id].parent_id;
    }

    Path.push(temp_id);
    while (!Path.empty()) {
        int p = Path.top();
        Path.pop();
        cout << "-> " << p << " ";
    }
    cout << endl;
}

double AStar(const vector<Node>& graph, int srcId, int destId) {
    if (!isValid(srcId, graph) || !isValid(destId, graph)) {
        cout << "Source or destination is invalid" << endl;
        return -1.0;
    }
    if (isDest(srcId, destId)) {
        cout << "Already at the destination" << endl;
        return 0;
    }

    // Initialize open set to keep track of nodes to be evaluated
    set<dPair> openSet;

    // Initialize cell details for each node in the graph
    map<int, Cell> cellDetails;
    for (int i = 0; i < graph.size(); i++) {
        cellDetails[i].f = FLT_MAX;
        cellDetails[i].g = FLT_MAX;
        cellDetails[i].h = FLT_MAX;
        cellDetails[i].parent_id = -1;
    }

    // Initialize the start node
    int i = srcId;
    cellDetails[i].f = 0.0;
    cellDetails[i].g = 0.0;
    cellDetails[i].h = calculateHVal(srcId, destId);
    cellDetails[i].parent_id = i;
    // Add start node to open set
    openSet.insert(make_pair(0.0, srcId));

    bool foundDest = false;

    // Main loop
    while (!openSet.empty()) {
        // Get the node from open set with the least 'f' value
        dPair p = *openSet.begin(); 
        openSet.erase(openSet.begin());

        int node = p.second; // Current node

        // Iterate over the neighbors of the current node
        for (const auto& neighbor : graph[node].neighbors) {
            int neighborId = neighbor.first;
            double neighborCost = neighbor.second;

            if (isDest(neighborId, destId)) { // Is neighbor the destination node?
                cellDetails[neighborId].parent_id = node; // Set parent of destination node
                tracePath(cellDetails, destId); // Trace the path from source to destination
                foundDest = true;
            }
            // Calculate new g, h, and f values for the neighbor node
            double gNew = cellDetails[node].g + neighborCost;
            double hNew = calculateHVal(neighborId, destId);
            double fNew = gNew + hNew;
            // Check if this path to neighbor is better than previous one
            if (cellDetails[neighborId].f == FLT_MAX || cellDetails[neighborId].f > fNew) {
                // Update details for the neighbor node
                openSet.insert(make_pair(fNew, neighborId));
                cellDetails[neighborId].f = fNew;
                cellDetails[neighborId].g = gNew;
                cellDetails[neighborId].h = hNew;
                cellDetails[neighborId].parent_id = node;
            }
        }
        // If destination is found, return the total cost of the path
        if (foundDest) {
            return cellDetails[destId].g;
        }
    }

    // Destination node not found
    if (!foundDest) {
        cout << "Failed to find the destination node" << endl;
        return -1.0;
    }
}

