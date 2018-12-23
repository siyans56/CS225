#include <queue>
#include <algorithm>
#include <string>
#include <list>

using namespace std;

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;

  // for (auto it : vertexMap) {
  //   for (auto iter : adjList.at(it.first)) {
  //     std::cout << it.first << ": " << iter->get().source().key() << "->" << iter->get().dest().key() << '\n';
  //   }
  // }




  std::unordered_map<string, pair<string, bool>> tab; //table for everything
  std::queue<std::string> q;
  for (auto it : vertexMap ) { //inserts info into the table
    tab.insert(make_pair(it.first, make_pair("", false) ));
  }

  tab.at(start).second = true; //vistis the first vertex

  q.push(start);
  while (!q.empty()) {
    string vertex = q.front(); // saves the vertex for later, then pops off queue

    q.pop();
    for (auto & e : adjList.at(vertex)) {
      if (e->get().directed()) { //if the edge is directed, then only check the destination for valid vertices
        if (tab.at(e->get().dest().key()).second == false) {
          tab.at(e->get().dest().key()).second = true; //sets the key to visited
          tab.at(e->get().dest().key()).first = vertex; //sets the previous vertex to the vertex in queue
          q.push(e->get().dest().key()); //pushes the destination onto the queue
        }
      }
      else {//check both source and destination as it could run both ways
        if (tab.at(e->get().dest().key()).second == false) {
          tab.at(e->get().dest().key()).second = true;
          tab.at(e->get().dest().key()).first = vertex;
          q.push(e->get().dest().key());
        }
        if (tab.at(e->get().source().key()).second == false) {
          tab.at(e->get().source().key()).second = true;
          tab.at(e->get().source().key()).first = vertex;
          q.push(e->get().source().key());
        }
      }
    }
  }

  path.push_front(end);
  string next = end;

  while (tab.at(next).first != "" ) { // runs the path
    std::cout << tab.at(next).first << '\n';
    path.push_front(tab.at(next).first);
    next = tab.at(next).first;
  }





  return path;
}
