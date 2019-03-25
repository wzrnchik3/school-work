/* File: Graph.cpp
 * Course: CS216-00x
 * Project: Project 3
 * Purpose: the implementation of member functions for the Graph class.
 *          it represents a undirected graph;
 *          it uses adjacency matrix representation (store 0 if no edge exists; store non-zero value(weight) if an edge exists)
 *
 */
#include <cassert>
#include <queue>
#include "Graph.h"

// constructor
Graph::Graph(int numVertices):adj(Matrix<int>(numVertices, numVertices, 0))
{
}

//return adjancency
Matrix<int> Graph::getAdjacency() const
{
    return adj;
}

// to check if an edge exists between v and w
// return true if an edge exists
// otherwise return false
bool Graph::hasEdge(int v, int w)
{
    assert(v>=0 && v < adj.GetSizeX() && w >=0 && w < adj.GetSizeX());
    if (adj(v, w)==0)
        return false;
    return true;
}

// add an edge between v and w (marked with value of edge)
void Graph::addEdge(int v, int w, int edge)
{
    assert(v>=0 && v < adj.GetSizeX() && w >=0 && w < adj.GetSizeX());
    adj(v,w) = edge;
    adj(w,v) = edge;
}

// return marked value from the edge v to w
int Graph::getEdge(int v, int w)
{
    assert(v>=0 && v < adj.GetSizeX() && w >=0 && w < adj.GetSizeX());
    return adj(v,w);
}

// Apply BFS traversal to find the shortest path from the given source s
// store the shortest path distance from the given source s in distance vector
// store the very next vertice to go throgh on the shortest path back to the given source s. For example go_through[w] = v, it means the shortest path from w to s needs to go through v: w->v--...->s
void Graph::BFS(int s, vector<int>& distance, vector<int>& go_through)
{
    // your code starts here
    int visited[distance.size()];
    for (int v = 0; v < distance.size(); v++) {
        visited[v] = false;
    }
    queue<int> Q;
    visited[s] = true;
    distance[s] = 0;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int w = 0; w < distance.size(); w++) {
            if (hasEdge(u, w) == true) {
                //go_through[w] = u;
                if (visited[w] == false) {
                    visited[w] = true;
                    distance[w] = distance[u]+1;
                    Q.push(w);
                    go_through[w] = u; // Make a path to the next node
                }
            }
        }
    }
}
