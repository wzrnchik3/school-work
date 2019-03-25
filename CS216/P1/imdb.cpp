/*
 * File: imdb.cpp
 * Course: CS216-00x
 * Project: Project 1
 * Purpose: Provide the implementation of the class named IMDB
 *          This class represents a movie-actor database
 */
#include <regex>  // needs c++11 standard
#include "imdb.h"

using namespace std;

// default constructor
IMDB::IMDB()
{
    //do nothing
    //since map class contains a default contructor
    //      which constructs an empty container, with no elements
}

// insert a pair <movieTitle, the set of actor names in this movie>
void IMDB::insert_a_movie(string movieTitle, set<string> actorNames) 
{
    // First upgrade movies_db
  // for each actorName in the set of actorNames insert movieTitle to its movie set
  for (auto it = actorNames.begin(); it != actorNames.end(); it++)
    {
      if (actors_db.find(*it) == actors_db.end())
	{
	  set<string> movies;
	  movies.insert(movieTitle);
	  actors_db[*it] = movies;
	}
      else
	{
	  actors_db[*it].insert(movieTitle);
	}
    }



    // Second upgrade actors_db
  // if the movie title name does not exist add the key to the map movies_db
  if (!isExistingMovie(movieTitle))
    movies_db[movieTitle] = actorNames;
  // if the key movieTitle does exist
  movies_db[movieTitle].insert(actorNames.begin(), actorNames.end());


}

// insert a pair<actorName, the set of movieTitle of this actor>
void IMDB::insert_an_actor(string actorName, set<string> movieTitles)
{
    // First upgrade actors_db
    // if the key actorName does not exist
    //        add the key to the map actors_db
    if (!isExistingActor(actorName))
        actors_db[actorName] = movieTitles;
    // if the key actorName does exist
    {
        actors_db[actorName].insert(movieTitles.begin(), movieTitles.end());
    }

    // Second upgrade movies_db
    // for each movieTitle in the set of movieTitles,
    // insert actorName to its actors set
    for (auto it = movieTitles.begin(); it != movieTitles.end(); it++)
    {
        if (movies_db.find(*it) == movies_db.end())
        {
            set<string> actors;
            actors.insert(actorName);
            movies_db[*it] = actors;
        }
        else
        {
            movies_db[*it].insert(actorName);
        }
    }
}

// use passing in parameter, movieTitle, as the pattern to match 
// one existing movie in the map
// return the matched movie title from the map
// otherwise return empty string
string IMDB::matchExistingMovie(string movieTitle) const
{
    string matchedMovie;
    bool found = false;
    // generate the regular expression to match 
    // which contains movieTitle as a substring
    // note that it performs case insensitive matching
    regex reg(movieTitle, regex_constants::icase);
    auto it = movies_db.begin();
    while (!found && it != movies_db.end())
    {
        if (regex_search(it->first, reg))
        {
            found = true;
            matchedMovie = it->first;
        }
        else
            it++;
    }
    return matchedMovie;
}

// check if a movieTitle does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingMovie(string movieTitle) const
{
  if (movies_db.find(movieTitle) != movies_db.end())
    return true;
  return false;
}

// check if an actorName does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingActor(string actorName) const
{
  if (actors_db.find(actorName) != actors_db.end())
    return true;
  return false;
}

// return a set of movie titles which actorName is in
// if the passing in parameter: actorName, is not in the database, 
//                   display message andreturn an empty set
set<string> IMDB::find_movies_for_an_actor(string actorName) const
{
  // if it is not in the db then cout an error and return empty set
  if (isExistingActor(actorName) == false)
    {
      cout << "There is no actor under that name in the database." << endl;
      set<string> empty;
      return empty;
    }
  // if it is in the db then make set movies and the value of the key actorName
  set<string> movies;
  const string actor = actorName;
  movies = actors_db.at(actor);
  return movies;
}

// return a set of actor names which are all in the movieTitle
// if the passing in parameter: movieTitle is not in the database, 
//                   display message and return an empty set
set<string> IMDB::find_actors_in_a_movie(string movieTitle) const
{
  // if it is not in the db then cout an error and return empty set
  if (isExistingMovie(movieTitle) == false)
    {
      cout << "There is no movie under that name in the database." << endl;
      set<string> empty;
      return empty;
    }
  // if it is in the db then make set actors and the value of the key movieTitle
  set<string> actors;
  actors = movies_db.at(movieTitle);
  return actors;
}
