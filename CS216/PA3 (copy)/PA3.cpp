/*
 *course: CS216-00x
 *Project: Project 3
 *Purpose: create a graph from given set of vertices and edges
 *         repeatedly ask the user to choose a source vertex (enter "Q" or "q" to quit)
 *         and calculate the shortest distance of each vertex to the source
 *         then display the shortest path from every vertex to the source
 *         It is a sub-problem of Project 3.
 *Author: Will Zrnchik
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>
#include "Graph.h"
#include "Matrix.h"

using namespace std;


int main()
{   
    // Read in from .txt files. Possible make into functions
    ifstream infile;
    string inputFile;
    // ask for input files
    cout << "Please enter the first file name, which contains actor IDs and names: (default file name is \"actors.txt\"): ";
    getline(cin, inputFile);
    if (inputFile != "")
        infile.open(inputFile.c_str()); // opens the input file given
    else
        infile.open("actors.txt");

    if (!infile.good()) 
    {
        cout << "Cannot open the file" << inputFile << endl;
        return 2;
    }
    long actorID;
    string actorName;
    map<long, string> idToActorMap;
    map<string, long> actorToIDMap;
    vector<long> actVertices;

    // go through file and create maps and a vector for finding verticies
    while (!infile.eof()) 
    {
        infile >> actorID >> ws;
        getline(infile, actorName);
        if (actorName != "") 
        {
            idToActorMap.insert(pair<long, string>(actorID, actorName));
            actorToIDMap.insert(pair<string, long>(actorName, actorID));
            actVertices.push_back(actorID);
        }
    }
    infile.close();

    cout << "Please enter the second file name, which contains movie IDs and names: (default file name is \"movies.txt\"): ";
    getline(cin, inputFile);
    if (inputFile != "")
        infile.open(inputFile.c_str()); // opens the input file given
    else
        infile.open("movies.txt");

    if (!infile.good())
    {
        cout << "Cannot open the file" << inputFile << endl;
        return 2;
    }
    long movieID;
    string movieName;
    map<long, string> movieMap;

    while (!infile.eof())
    {
        infile >> movieID >> ws;
        getline(infile, movieName);
        if (movieName != "")
        {
            movieMap.insert(pair<long, string>(movieID, movieName));
        }
    }
    infile.close();
    // COUT TO TEST

    
    cout << "Please enter the third file name, which contains actor IDs and movie IDs: (default file name is \"movie-actor.txt\"): ";
    getline(cin, inputFile);
    if (inputFile != "")
        infile.open(inputFile.c_str()); // opens the input file given
    else
        infile.open("movie-actor.txt");

    if (!infile.good())
    {
        cout << "Cannot open the file" << inputFile << endl;
        return 2;
    }
    vector<long> movieIDvec;
    vector<long> actorIDvec;

    while (!infile.eof())
    {
        long movTemp;
        long actTemp;
        infile >> movTemp >> ws;
        infile >> actTemp;
        if (movieIDvec.empty() && actorIDvec.empty())
        {
            movieIDvec.push_back(movTemp);
            actorIDvec.push_back(actTemp);
        }
        else if (movieIDvec.back() != movTemp || actorIDvec.back() != actTemp)
        {
            movieIDvec.push_back(movTemp);
            actorIDvec.push_back(actTemp);
        }

    }
    infile.close(); // close file
    Graph actorMovieGraph(idToActorMap.size());

    for (int i = 0; i < idToActorMap.size(); i++)
    { 
        for (int j = 0; j < actorIDvec.size(); j++)
        {
            if (actVertices[i] == actorIDvec[j])
            {
                for (int k = i + 1; k < idToActorMap.size(); k++)
                {
                    for (int l = 0; l < actorIDvec.size(); l++)
                    {
                        if (actVertices[k] == actorIDvec[l] && movieIDvec[j] == movieIDvec[l])
                        {
                            actorMovieGraph.addEdge(i, k, movieIDvec[j]);    
                        }              
                    }
                }
            }
        }
    }
    // make bacon int source and find it by going through vectors
    int baconSource;
    string baconString = "Kevin Bacon";
    for (int bIndex = 0; bIndex < actVertices.size(); bIndex++)
    {
        if (actVertices[bIndex] == actorToIDMap.find(baconString)->second)
            baconSource = bIndex;
    }
    // make graph distance and go throughs using BFS
    vector<int> distance(idToActorMap.size(), -1);
    vector<int> go_through(idToActorMap.size(), -1);
    actorMovieGraph.BFS(baconSource, distance, go_through);
    string inputActor;
    // loop to get actor name
    while (inputActor != "q" && inputActor != "Q")
    {
        int errorCheck = -1;
        cout << "\nPlease enter an actor to find the Bacon Number for (case-sensitive, enter q or Q to quit): ";
        getline(cin, inputActor);
        for (int m = 0; m < actVertices.size(); m++)
        {
            if (actVertices[m] == actorToIDMap.find(inputActor)->second)
            {
                cout << "Bacon number for " << inputActor << " is " << distance[m] << endl;
                cout << idToActorMap.find(actVertices[m])->second << " appeared in " << movieMap.find(actorMovieGraph.getEdge(m, go_through[m]))->second  << " with ";
                for (int n = m; go_through[n] != baconSource; n = go_through[n]) 
                {
                    cout << idToActorMap.find(actVertices[go_through[n]])->second << endl;
                    cout << idToActorMap.find(actVertices[go_through[n]])->second << " appeared in " << movieMap.find(actorMovieGraph.getEdge(go_through[n], go_through[go_through[n]]))->second << " with ";
                }
                cout << idToActorMap.find(actVertices[baconSource])->second << endl;
                errorCheck++;
            }
          
        }       
        if (errorCheck == -1 && inputActor != "q" && inputActor != "Q")
            cout << inputActor << " is an invalid entry, please try again." << endl;   
    }
    return 0;
}