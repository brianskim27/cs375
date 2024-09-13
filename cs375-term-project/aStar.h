#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
// #include <limits>
// #include <set>
// #include <cmath>
// #include <stack>
#include <bits/stdc++.h>

#include "graph.h"
using namespace std;

#define ROW 100
#define COL 100

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> doublePair;
typedef pair<double, int> dPair;

/*
struct Node {
    int id;
    vector<pair<int, double>> neighbors;
};
*/

/*
// holds necessary parameters for algorithm
struct Cell {
    // row and column of parent
    int parent_i, parent_j;
    // f = g + h, g = cost from start to current node, h = estimated cost from current node to dest node
    int f, g, h;
};
*/

// holds necessary parameters for algorithm
struct Cell {
    // row and column of parent
    int parent_id;
    // f = g + h, g = cost from start to current node, h = estimated cost from current node to dest node
    double f, g, h;
};

// checks if a node is a valid cell, is row and column number in range?
bool isValid(int nodeId, const vector<Node>& graph);

// checks if destination cell was reached
bool isDest(int nodeId, int destId);

// calculate utility value 'h'
double calculateHVal(int nodeId, int destId);

// trace path from source to destination
void tracePath(map<int, Cell> cellDetails, int destId);

// shortest path A* algorithm
double AStar(const vector<Node>& graph, int srcId, int destId);

#endif //ASTAR_H