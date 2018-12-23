/* Your code here! */
#include "dsets.h"

using namespace std; /* std */

DisjointSets::DisjointSets() {

}
//each "node" is an independent set, so each have size -1
void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    vec.push_back(-1); //-1 for unconnected elements
  }
}

int DisjointSets::find(int elem) {
  if (vec[elem] < 0) { //if negative, at root
    return elem;
  }
  else {
    int root = find(vec[elem]); //get the ultimate root so that each node can point to the real root
    vec[elem] = root; //set it to the ultimate root
    return root;
  }

}

// This function should be implemented as union-by-size.

// That is, when you setunion two disjoint sets,
//  the smaller (in terms of number of nodes)
//  should point at the larger. This function works as described in lecture,
//  except that you should not assume that the arguments to setunion
//  are roots of existing uptrees.
//
// Your setunion function SHOULD find the roots of its arguments
// before combining the trees. If the two sets are the same size,
// make the tree containing the second argument point to the tree
// containing the first. (Note that normally we could break this
// tie arbitrarily, but in this case we want to control things for grading.)

void DisjointSets::setunion(int a, int b) {
  int as = find(a), bs = find(b); //find the roots of both sets
  int combo = vec[as] + vec[bs]; //add together for comparison

  if (as == bs) return;
  if (vec[as] > vec[bs]) { //if a is larger, b points to a, and a holds the new size
    vec[bs] = as;
    vec[as] = combo;
  }
  else { //same thing bubt for larger b
    vec[as] = bs;
    vec[bs] = combo;
  }
}

int DisjointSets::size(int elem) {
  if (vec[elem] < 0) { // if a negative number, is a root node that will have -size
    return (vec[elem]) * -1;
  } //otherwise, will point to root
  return size(vec[elem]); //node is pointing to its parent node, which will have size. re-run there
}
