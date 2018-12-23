#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>



/* NOTES:
 the adjacency list stores a pointer (iterator) to a location in the edgelist
 that will be the start of the adjacent edges of that key (vertex)
*/

//ONLY CHECK FOR DIRECTED IN REMOVEEDGE
// ASSUME UNDIRECTED

// for (edgeListIter it : adjList.at(key)) {
//
// }

// EACH VERTEX HAS ITS OWN LIST OF Edges
// EDGELIST IS A MASTER LIST
// THE INDIVIDUAL LIST OF EDGES CONTAINS ITERATORS THAT ACT AS POINTERS
// TO THE REQUESTED EDGE IN THE MASTER LIST


/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size(); //size of vertex map is all vertices
}

/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  //apparently this degreee is supposed to be only edges that
  // are outgoing but they dont test that, so just all edges
  return adjList[v].size(); //size of individual list is all edges (both directions)
}

/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.emplace(key, v); // add to vertexMap
  std::list<edgeListIter> elist; //creating new list for new vertex
  adjList.emplace(key, elist); //add to AdjList
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2

  //TODO: Remove from the vertexMap
  vertexMap.erase(key);

  //TODO: Remove associated edges
  std::list<E_byRef> list = incidentEdges(key); //gets a list of all associated edges

  //TODO: Update AdjList for adjacent vertices
  // for (auto e : adjList.at(key)) { // e is now the edgeListIter
  //   removeEdge(e->get().source(),e->get().dest()); //call remove edge on iterator
  // }

  for (auto & e : list) {
    removeEdge(e.get().source().key(), e.get().dest().key()); //use get to get the edge reference
  }

  adjList.erase(key); //remove vertex from adjlist



  // for (int i = 0; i < list.size(); i++) {
  //   E & e = list[i].get();
  //   removeEdge(e);//.get()); //use get to get the edge reference
  // }
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  /*
  If we insertFront into the edge list a new edge (a -> b)
  such that we have an edge list (a -> b) -> nextEdge -> ... -> NULL (end)

  if we do edgeList.begin() we get an iterator that current
  references the edge (a -> b)

  We can then appropriately add said iterator to the appropriate adjList.

  */
  E & e = *(new E(v1, v2));
  E & check = edgeList.front();
  bool directed = e.directed();

  //TODO: Add to edgelist
  edgeList.push_front(e);
  edgeListIter it = edgeList.begin();

  //TODO: Add to Adjacency lists
  adjList.at(v1.key()).push_front(it); //add to individual edgelist
  // if (!check.directed()) { //if false, then it is undirected, go both ways
  adjList.at(v2.key()).push_front(it); //add to other edgelist
  // }

  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  // NOTE: If runtime is too long, look at adj list
  //std::cout << "testing key remove" << '\n';
  //std::cout << "key1:" << key1 << '\n';
  //std::cout << "key2:" << key2 << '\n';

  //TODO: Find out if it is directed or not. Find the edge
  E & ed = edgeList.front();
  bool directed = ed.directed();

  // V & v1(key1); //temp to compare
  // V & v2(key2); // temp to compare
  std::list<edgeListIter> edges = adjList[key1];
  Edge toRemove = Edge(key1,key2);

  // for (auto & e : edgeList) { //for all edges in the master list
  //   if (e.get().source() == v1  && e.get().dest() == v2) { //if equal, remove
  //     edgeList.remove(e); //std::list remove func
  //     break;
  //   }
  // }

  //TODO: Remove edge from Adjlists (removing the iterators)
  //std::cout << "CHECK" << '\n';




  for (auto & e : adjList.at(key1)) { //for all edges in the first adjlist
    //std::cout << "get directd:" << e->get().directed() <<'\n';
    if (e->get() == toRemove) { //if found
      //std::cout << "REACHED" << '\n';
      removeEdge(e); //remove the iterator within the list
      break;
    }
  }
  if (!directed) { //undirected, so remove from both ways
    Edge reversetoRemove = Edge(key2,key1); //check against
    for (auto & e : adjList.at(key2)) {
      if (e->get() == reversetoRemove) {
        //std::cout << "REACHED UNDIRECTED" << '\n';
        removeEdge(e); //remove the iterator within the list
      }
    }
  }

  //
  // std::list<edgeListIter> edges = adjList[key1];
  // Edge toRemove = Edge(key1,key2);
  // for (auto edgeIt : edges) {
  //   if (edgeIt->get() == toRemove) {
  //     removeEdge(edgeIt);
  //   }
  // }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  const E & e = *it;
  //std::cout << "CHECK" << '\n';
  E & ed = edgeList.front();
  bool directed = ed.directed(); //check if graph has directed or undirected edges

  edgeList.erase(it); //remove the actual edge from edgeList
  //std::cout << "CHECK2" << '\n';

  V v1 = e.source();
  //std::cout << "CHECK3" << '\n';
  adjList.at(v1.key()).remove(it); //delete directed version's
  //std::cout << "CHECK4" << '\n';
  if (!directed) { //undirected, delete other way too
    //std::cout << "CHECK5" << '\n';
    V v2 = e.dest();
    //std::cout << "CHECK6" << '\n';
    adjList.at(v2.key()).remove(it); //iinvalid read of size 8
    //std::cout << "CHECK7" << '\n';
  }
  // delete *it;

  //
  // for (auto & edge : adjList.at(e.source().key())) { //find within source->dest
  //   if (edge->get().dest() == e.dest()) {
  //     adjList.at(e.source().key()).remove(*e);
  //   }
  // }
  // if (!directed) {
  //   for (auto & edge : adjList.at(e.dest().key())) { //find within dest->source
  //     if (edge->get().dest() == e.source()) { //if the edges start is the dest, remove
  //       adjList.at(e.dest().key()).remove(*e);
  //     }
  //   }
  // }
  // e.source().key().remove();
  // e.dest().key().remove();

}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  // V & v(key);

  std::list<std::reference_wrapper<E>> edges;
  for (auto & e : adjList.at(key)) { // e is now the edgeListIter
    edges.push_back(*e);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  // iterate thru both adjlists and check. Make logic for undirected/directed
  E & ed = edgeList.front();
  bool directed = ed.directed(); //grab an edge to cehck if graph is un/directed
  V v1(key1); //temp to compare
  V v2(key2); // temp to compare

  //directed case: only adjacent if key1 --> key2
  for (auto & e : adjList.at(key1)) { //for all edges in the first adjlist
    if (e->get().dest() == v2) { //if theres an edge going to the second node
      return true; //remove the iterator within the list
    }
  }
  // if (!directed) { //undirected, check both ways
  //   for (auto & e: adjList.at(key2)) {
  //     if (e->get().dest() == v1) { //if theres an edge going to the first node
  //       return true; //remove the iterator within the list
  //     }
  //   }
  // }
  return false;
}
