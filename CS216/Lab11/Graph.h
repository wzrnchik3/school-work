/* File: Graph.h
 * Course: CS216-00x
 * Project: Project 3
 * Purpose: the declaration for the Graph class.
 *          it represents a undirected graph;
 *          it uses adjacency matrix representation (store 0 if no edge exists; store non-zero value(weight) if an edge exists)
 *** DO NOT CHANGE THE DECLARATION OF Graph CLASS ***
 *
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "Matrix.h"
 
using namespace std;
 
class Graph
{
    public:
        // constructor
        Graph(int numVertices);

        // return the private data member 
        // as the adjacency representation of the Graph
        Matrix<int> getAdjacency() const;

        // to check if an edge exists between v and w
        // return true if an edge exists
        // otherwise return false
        bool hasEdge(int v, int w);

        // add an edge between v and w (marked with value of edge)
        void addEdge(int v, int w, int edge);

        // return marked value from the edge v to w
        int getEdge(int v, int w); 

        // Apply BFS traversal to find the shortest path from the given source s
        // store the shortest path distance from the given source s in distance vector
        void BFS(int s, vector<int>& distance);

    private:    
        Matrix<int> adj;        // using adjancy matrix representation
};

#endif   /* GRAPH_H */
