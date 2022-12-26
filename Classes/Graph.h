

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

class Graph {
    struct Edge {
        string dest;
        string company;
    };

    struct Node {
        string src;
        list<Edge> adj;
        bool visited;   // As the node been visited on a search?

    };

    int n;
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(string src, string dest, string company, int pos);

    void verNodes();
};

#endif
