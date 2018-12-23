/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"
#include <iostream>
using namespace std;

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  // loop thru starting graph to get edges and vertices. Then add to both
  // residual and flow
  // residual has to have reverse edges too

  // for (auto & node : g_.adjacency_list) { //for each node in the graph
  //   for (auto & dest : node) { //for every connected node from current node
  //
  //   }
  // }
  vector<Vertex> verts = g_.getVertices();
  for (size_t i = 0; i < verts.size(); i++) {
    Vertex v = verts[i];
    //cout << "Inserting vertex: " << v << endl;
    residual_.insertVertex(v);
    flow_.insertVertex(v);
  }

  vector<Edge> edges = g_.getEdges();
  for (size_t i = 0; i < edges.size(); i++) {
    Edge e = edges[i];
    //cout << "Inserting edge to residual: " << e.source << e.dest << endl;
    residual_.insertEdge(e.source, e.dest);
    //cout << "Setting initial weight to: " << e.getWeight() << endl;
    residual_.setEdgeWeight(e.source, e.dest, e.getWeight());

    //cout << "Inserting reverse edge to residual: " << e.dest << e.source << endl;
    residual_.insertEdge(e.dest, e.source); //adding reverse edges
    residual_.setEdgeWeight(e.dest, e.source, 0); //set reverse edge to 0

    //cout << "Inserting edge to flow: " << e.source << e.dest << endl;
    flow_.insertEdge(e.source, e.dest);
    flow_.setEdgeWeight(e.source, e.dest, 0);
  }

  /*
  Adj list is a map with a node as key and a map of all connected nodes as value
  */

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // find the minimum weight among the edges in the path in the residual graph by
  // iterating through the vertices in the path vector.
  // YOUR CODE HERE
  int min = 100000;
  for (size_t i = 0; i < path.size()-1; i++) { //checking every node but last
    Edge e = residual_.getEdge(path[i], path[i+1]);
    //cout << "Current edge weight: " << e.getWeight() << endl;
    min = (e.getWeight() < min) ? e.getWeight() : min;
  }
  //cout << "Min (pathCap): " << min << endl;
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  //use  findAugmentingPath until you cant
  // YOUR CODE HERE
  //cout << "START" << endl;
  vector<Vertex> v;
  // findAugmentingPath(source_, sink_, v);
  // int cap = pathCapacity(v);
  int max = 0;
   while (findAugmentingPath(source_, sink_, v)) { //should be empty if no more paths
  // while (cap != -1) { //cap == -1 when no valid path
    //cout << "Loop.. vec size: " << v.size() << endl;
    int cap = pathCapacity(v);
    // max = (max > cap) ? max : cap;
    max += cap;
    for (size_t i = 0; i < v.size()-1; i++) {
      // Subtract cap from forward edges
      residual_.setEdgeWeight(v[i], v[i+1], residual_.getEdgeWeight(v[i],v[i+1])-cap);
      // Add the capacity to the reverse edges in the residual graph.
      residual_.setEdgeWeight(v[i+1], v[i], residual_.getEdgeWeight(v[i+1],v[i])+cap);

      // Add the capacity to the edges in the corresponding path in the flow graph.
      // Note that this path may go in the opposite direction of the edge in your graph.
      // In that case, reverse the vertices and subtract the capcity from the edge in the flow graph
      if (!flow_.edgeExists(v[i],v[i+1])) { //if the flow doesnt exist, must be reversed
        //cout << "Reverse edge"<< endl;
        flow_.setEdgeWeight(v[i+1], v[i], flow_.getEdgeWeight(v[i+1],v[i])-cap);
      }
      else { //normal edge, add capacity
        //cout << "Normal edge"<< endl;
        flow_.setEdgeWeight(v[i], v[i+1], flow_.getEdgeWeight(v[i],v[i+1])+cap);
      }
    }
    // findAugmentingPath(source_, sink_, v);
  }
  maxFlow_ = max;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
