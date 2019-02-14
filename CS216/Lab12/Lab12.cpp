/*
 *course: CS216-00x
 *Project: Lab 12 (as part of Project 3)
 *Purpose: create a graph from given set of vertices and edges
 *         repeatedly ask the user to choose a source vertex (enter "Q" or "q" to quit)
 *         and calculate the shortest distance of each vertex to the source
 *         then display the shortest path from every vertex to the source
 *         It is a sub-problem of Project 3.
 *Author: (your name)
 */

#include <iostream>
#include <vector>
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

    int source;

    while (true)
    {
        cout << "Please choose the vertex as the source (integer range [0,6]) (type 'Q' or 'q' to quit): " << endl;
	    cin >> source;
        cin.ignore(256, '\n');
        
        if (cin.fail())
        {
            string check_input;
            cin.clear();
            cin >> check_input;
            if (check_input == "Q" || check_input == "q")
                break;
            else {
                cout << "Invalid input, please try again..." << endl;
                continue;
            }    
        }

        if (source < 0 || source > 6)
            cout << "your input is not in the correct range, please try again..." << endl;
        else
        {
            cout << endl;
            cout << "Breadth First Traversal "
                 << "(starting from the source vertex: "<< source << " )" << endl;
            vector<int> distance(VERTICESNUM, -1);
	        vector<int> go_through(VERTICESNUM, -1);
            testingGraph.BFS(source, distance, go_through);
            // Display the distance of each vertex(except for the source itself) to the source vertex
            // Display the shortest path from each vertex(except for the source itself) to the source 
            // the distance is defined as the number of edges
            // the distance of the source to the source is 0
            // there is no path from the source to a vertex if its distance is -1
            // Your code starts here......
            for (int i = 0; i < distance.size(); i++)
            {
                if ( i != source)
                {
                    if (distance[i] != -1) 
                    {
                        cout << "The distance from source vertex " << source << " to vertex " 
                            << i << " is " << distance[i] << "-edge away." << endl;
                        cout << "The path back to the source vertex:" << endl;
                        cout << i << " --> ";
                        for (int j = i; go_through[j] != source; j = go_through[j]) {
                            cout << go_through[j] << " --> ";
                        }
                        cout << source << endl;
                    }
                    else
                        cout << "There is no path to vertex " << i << endl;
                }    
            }
        }
    }
    return 0;
}

