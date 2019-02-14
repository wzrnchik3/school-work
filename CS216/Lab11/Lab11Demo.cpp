/*
 *course: CS216-00x
 *Project: Lab 11 (For Demonstration only)
 *Purpose: first part, creating a graph from given set of vertices and edges
                       then calculate the total number of edges in the undirected graph
           second part, creating two matrices of randomly generated double floating-point numbers
                        in the range of [0.1, 1.0], then calculate the addition of two
 **** PLEASE DO NOT CHANGE THIS FILE ****
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"
#include "Graph.h"

using namespace std;

int main()
{
    // Create a graph given by Figure 1 of Project 3
    const int VERTICESNUM = 7;
    Graph testingGraph(VERTICESNUM);
    testingGraph.addEdge(0, 2, 150);
    testingGraph.addEdge(0, 6, 150);
    testingGraph.addEdge(2, 6, 150);
    testingGraph.addEdge(1, 3, 1472);
    testingGraph.addEdge(2, 4, 2268);
    testingGraph.addEdge(3, 6, 3555);
    testingGraph.addEdge(3, 5, 3979);

    // Calculate totally how many edges in the undirected graph, testingGraph
    int totalEdges = 0;

    for (size_t i = 0; i < VERTICESNUM; i++)
    {
        for (size_t j = 0; j < VERTICESNUM; j++)
        {
            if (testingGraph.hasEdge(i, j))
                totalEdges = totalEdges + 1;
        }
    }
    
    // the edge between u and v has been counted twice in the above nested loop
    // since it is a undirected graph
    // the total edge should be totalEdges/2
    totalEdges = totalEdges / 2;

    // display the adjacency representation of the graph, testingGraph
    cout << testingGraph.getAdjacency() << endl;

    // display the total edges in the undirected graph, testingGraph
    cout << "The total edges in the above undirected graph is: " << totalEdges << endl;


    // The rest part is for testing Matrix class only
    // create two ROW*COLUMN matrices
    // store randomly generated data items 
    // and apply matrix addition
    const int ROW = 3;
    const int COLUMN = 5;
    const int MAX = 10; 

    Matrix<double> testingMatrix1(ROW, COLUMN);
    Matrix<double> testingMatrix2(ROW, COLUMN);

    srand(time(0));
    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j=0; j < COLUMN; j++)
        {
            int random = rand() % MAX + 1;
            testingMatrix1(i,j) =  (double)random / MAX;
            random = rand() % MAX + 1;
            testingMatrix2(i,j) = (double)random / MAX;
        }
    }

    cout << "The first matrix is: " << endl;
    cout << testingMatrix1 << endl;
    cout << "The second matrix is: " << endl;
    cout << testingMatrix2 << endl;
    cout << "The addition of two matrices is: " << endl;
    cout << testingMatrix1 + testingMatrix2 << endl;

    return 0;
}

