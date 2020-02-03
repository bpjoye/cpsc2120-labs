/*
 * Name: Ben Joye
 * Date Submitted: 11/2/18
 * Lab Section: 3
 * Assignment Name: Lab 09
 */

#pragma once

#include <string>
#include "heap.h"
#include <algorithm>
#include <climits>
#include <map>
#include <vector>
#include <set>

using namespace std;

typedef std::string node;

struct edge {
  node dest;
  int dist;
  edge(node dest, int dist): dest(dest), dist(dist){}
  bool operator<(const edge&b) {
    if (this->dist < b.dist) {
      return false;
    }
    return true;
  }
};

struct kEdge {
  node init;
  node dest;
  int dist;
  kEdge(node init, node dest, int dist): init(init), dest(dest), dist(dist){}
};

bool compare(const kEdge &a, const kEdge &b) {
    return a.dist < b.dist;
}

class graphalgs {
private:
  map<node,vector<edge>> graph;
public:
    void add_edge(node node1, node node2, int distance);
    void dijkstra(node firstNode);
    void kruskal();
    bool cycle(vector<kEdge> v);
    bool cycleRecursive();
};

//adds two nodes that are directly connected and their distances
//all edges will be added before dijkstra and kruskal are called
void graphalgs::add_edge(node node1, node node2, int distance) {
  edge e(node2,distance);
  graph[node1].push_back(e);
}

//prints the minimum distance from the source node to the other nodes
void graphalgs::dijkstra(node sourceNode) {

  // create an edge object for the source node
  edge sourceEdge(sourceNode,0);
  edge front("",0);

  // stores the nodes to visit next
  heap<edge> minHeap;
  // stores all distances to all nodes
  map<node,int> distanceTable;
  // stores all nodes visited
  set<node> placesVisited;

  minHeap.push(sourceEdge);

  // fill distance table with infinity
  for (auto const& it : graph) {
    distanceTable[it.first] = INT_MAX;
    for (int i = 0; i < (int)it.second.size(); i++) {
      distanceTable[it.second[i].dest] = INT_MAX;
    }

  }
  distanceTable[sourceNode] = 0;

  int d;
  // loop until the min heap is empty
  while (minHeap.size() > 0) {
    // get the front of the min heap
    front = minHeap.front();
    // if it hasn't been visited yet
    if (!placesVisited.count(front.dest)) {
      // add it to the visited nodes
      placesVisited.insert(front.dest);
      // get all connecting nodes
      vector<edge> v = graph[front.dest];
      // loop through them
      for (int i = 0; i < (int)v.size(); i++) {
        // calculate new distance
        d = v[i].dist + front.dist;
        // if its smaller than the previous distance, update it
        if (d < distanceTable[v[i].dest]) {
          distanceTable[v[i].dest] = d;
          minHeap.push(edge(v[i].dest,d));
        }
      }

    }
    // remove the front node from the heap
    minHeap.pop();
  }

  cout << "Dijkstra (from " << sourceNode << ")" << endl;
  for (auto const& it : distanceTable) {
    cout << it.first << ", " << it.second << endl;
  }
  cout << endl;
}


bool graphalgs::cycle(vector<kEdge> v) {
  return false;
}

bool graphalgs::cycleRecursive() {
  return false;
}

//prints the edges of the graph that create a minimum spanning tree
void graphalgs::kruskal() {

  // vector for all edges
  vector<kEdge> edgeList;
  // vector for edges in the MST
  vector<kEdge> minSpanningTree;

  // add all edges from the graph to the edge list
  for (auto const& it : graph) {
    vector<edge> v = it.second;
    for (int i = 0; i < (int)v.size(); i++) {
      kEdge e(it.first,v[i].dest,v[i].dist);
      edgeList.push_back(e);
    }
  }

  // sort the edge vector
  sort(edgeList.begin(), edgeList.end(), compare);

  int i = 0;
  // loop through the edge list
  while ((minSpanningTree.size() != graph.size()-1) && i < (int)edgeList.size()) {
    kEdge e = edgeList[i];
    // add the edge to the MST
    minSpanningTree.push_back(e);
    // if it adds a cycle, remove that value
    if (cycle(minSpanningTree)) {
      minSpanningTree.pop_back();
    }
    i++;
  }

  cout << "Kruskal" << endl;
  for (int x = 0; x < (int)minSpanningTree.size(); x++) {
    cout << minSpanningTree[x].init << ", " << minSpanningTree[x].dest << ", " << minSpanningTree[x].dist << endl;
  }
  cout << endl;

}
