/*
 * Name: Ben Joye
 * Date Submitted: 9/28/18
 * Lab Section: 003
 * Assignment Name: Lab 5
 */

#pragma once

#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

//This class represents a map of all of the cities
//feel free to add to this class but do not remove anything
class worldmap{
  private:
    map<string, vector<pair<string, int>>> theMap;
    vector<string> placesVisited;
    int distanceTravelled = 0;
    void breath_first_search(string city1, string city2);
    void depth_first_search(string city1, string city2);
  public:
    void add_pair_to_map(string city1, string city2, int distance);
    void find_path(string city1, string city2);
};

//Implement all of the functions below

//takes in two cities that are connected, the distance between them,
//and stores the values
void worldmap::add_pair_to_map(string city1, string city2, int distance){
  theMap[city1].push_back(make_pair(city2,distance));
  theMap[city2].push_back(make_pair(city1,distance));
}

//finds the path between two cities using breath first search
//prints out cities visited during the search
//as well as the total distance traveled
void worldmap::breath_first_search(string city1, string city2) {
  cout << "BFS: ";
  queue<pair<string,int>> q;
  string city_1 = city1;
  string prevCity = city1;
  bool found = false;

  // add the beginning city to the queue
  q.push(make_pair(city1,0));
  placesVisited.push_back(city1);

  // loop while the destination has not been found
  while (!found) {

    // copy the vector at the current city
    vector<pair<string, int>> v = theMap[city_1];
    int size = v.size();

    // loop through that vector
    for (int x = 0; x < size; x++) {
      // make sure that the city you're going to isn't the one you're coming from
      if (prevCity != v[x].first) {
        // add the string and distance to the queue
        q.push(make_pair(v[x].first, v[x].second));
        // add the string and distance to the vector to be printed out at the end
        placesVisited.push_back(v[x].first);
        distanceTravelled += v[x].second;
        // if the city you're going to is the destination, then end the loop
        if (v[x].first == city2) {
          found = true;
        }
      }
    }
    // set previous city to the city you just added
    prevCity = q.front().first;
    // pop off that city
    q.pop();
    // set the new city to the next city in the queue
    city_1 = q.front().first;
  }

  // prints out cities visited and distance travelled in correct formatting
  int s = placesVisited.size();
  for (int x = 0; x < s-1; x++) {
    cout << placesVisited[x] << ", ";
  }
  cout << placesVisited[s-1] << "; ";
  cout << "distance travelled: " << distanceTravelled << endl;
  placesVisited.clear();
  distanceTravelled = 0;
}

//finds the path between two cities using depth first search
//prints out cities visited during the search
//as well as the total distance traveled
void worldmap::depth_first_search(string city1, string city2) {

  cout << "DFS: ";
  stack<pair<string,int>> q;
  string city_1 = city1;
  string prevCity = city1;
  bool found = false;

  // adds the starting city to the stack
  q.push(make_pair(city1,0));
  placesVisited.push_back(city1);

  // while the destination has not been found
  while (!found) {

    // set the previous city to the city you're coming from
    prevCity = city_1;
    // set the new city to the top of the stack
    city_1 = q.top().first;
    // pop off the city being checked from the stack
    q.pop();

    // copy the vector in the map at the current city
    vector<pair<string, int>> v = theMap[city_1];
    int size = v.size();

    // loop backwards through that vector
    for (int x = size-1; x >= 0; x--) {
      // make sure that the city isn't the one you're coming from
      if (prevCity != v[x].first) {
        // add that city to the stack
        q.push(make_pair(v[x].first, v[x].second));
      }
    }
    // add the top of the stack to placesVisited
    placesVisited.push_back(q.top().first);
    // add distance travelled
    distanceTravelled += q.top().second;

    // if thhe destination is on the top of the stack, end the loop
    if (q.top().first == city2) {
      break;
    }

  }
  // prints out the cities and distance in correct formatting
  int s = placesVisited.size();
  for (int x = 0; x < s-1; x++) {
    cout << placesVisited[x] << ", ";
  }
  cout << placesVisited[s-1] << "; ";
  cout << "distance travelled: " << distanceTravelled << endl;
  placesVisited.clear();
  distanceTravelled = 0;
}

//this function finds the path between two cities
//using breath_first_search first and then depth_first_search
void worldmap::find_path(string city1, string city2){
  breath_first_search(city1,city2);
  depth_first_search(city1,city2);
}
