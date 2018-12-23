/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
#include <iostream>
#include <random>
using namespace std;

/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    //cout << "Starting: "<< startingTokens << endl;

    if (startingTokens == 1) {
      Vertex s = "p1-1";
      Vertex e = "p2-0";
      g_.insertVertex(s);
      g_.insertVertex(e);

      g_.insertEdge(s,e);
      g_.setEdgeWeight(s,e,0);
      startingVertex_ = s;
    }

    for (int tokens = 0; tokens <= (int)startingTokens; tokens++) { //create the vertices
      // std::stringstream curr;
      // curr<<"p1-"<<tokens;
      // Vertex s1 = curr.str();
      Vertex s1 = "p1-" + to_string(tokens);
      g_.insertVertex(s1);
      Vertex s2 = "p2-" + to_string(tokens);
      g_.insertVertex(s2);

      if (tokens == (int)startingTokens) {
        startingVertex_ = s1;
      }
    }
    //cout << "Check: "<< startingTokens << endl;

    //create the Edges and set weights to 0
    for (int i = (int)startingTokens; i >= 1; i--) {
      //p1 edges
      Vertex src = "p1-" + to_string(i);
      Vertex e1 = "p2-" + to_string((i-1 >= 0) ? i-1 : 0);
      Vertex e2 = "p2-" + to_string((i-2 >= 0) ? i-2 : 0);
      //cout << "inserting " << src << " and "<< e1 << endl;
      g_.insertEdge(src, e1);
      g_.setEdgeWeight(src, e1, 0);
      //cout << "inserting " << src << " and "<< e2 << endl;
      g_.insertEdge(src, e2);
      g_.setEdgeWeight(src, e2, 0);

      //p2 edges
      Vertex src2 = "p2-" + to_string(i);
      Vertex e12 = "p1-" + to_string((i-1 >= 0) ? i-1 : 0);
      Vertex e22 = "p1-" + to_string((i-2 >= 0) ? i-2 : 0);
      g_.insertEdge(src2, e12);
      g_.setEdgeWeight(src2, e12, 0);
      g_.insertEdge(src2, e22);
      g_.setEdgeWeight(src2, e22, 0);


    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
 // cout << "Random 1: " << rand() % 51 << endl;
 // cout << "Random 2: " << rand() % 51 << endl;
 // int tokens;
 // if (startingVertex_ == "p1-10") tokens = 10;
 // else tokens = (int)startingVertex_[3] - '0';
 // // cout << "startingVertex_ str" << startingVertex_ << endl;
 // // cout << "Random: Start tokens: "<< tokens << endl;
 // if (tokens == 1) { //nimLeaner(1) edge case
 //   path.push_back(g_.getEdge("p1-1","p2-0"));
 //   return path;
 // }
 //
 // //TODO: use startingVertex_ to figure out token amount
 // for (int i = tokens; i >= 0; i--) {
 //   // cout << "run" << endl;
 //   //player 1 move
 //   int diff = i - ((rand() % 2) + 1); //either 1 or 2
 //   // cout << "diff: " << diff << endl;
 //   if (diff <= 0) { //if wll reach 0, end
 //     // cout << "Entered p1 endgame" << endl;
 //     Vertex src = "p1-" + to_string(i);
 //     Vertex dest = "p2-0";
 //     path.push_back(g_.getEdge(src,dest));
 //
 //     //debugging
 //     // for (auto & edge : path) {
 //     //   cout << edge.source << " " << edge.dest << endl;
 //     // }
 //
 //     return path;
 //   }
 //   else {
 //     Vertex src = "p1-" + to_string(i);
 //     Vertex dest = "p2-" + to_string(diff);
 //     path.push_back(g_.getEdge(src, dest));
 //   }
 //
 //   //Player 2 move
 //   int diff2 = diff-((rand() % 2) + 1); //either 1 or 2
 //   // cout << "diff2: " << diff2 << endl;
 //
 //   if (diff2 <= 0) { //if wll reach 0, end
 //     // cout << "Entered p2 endgame" << endl;
 //     Vertex src = "p2-" + to_string(i);
 //     Vertex dest = "p1-0";
 //     path.push_back(g_.getEdge(src,dest));
 //     // cout << "Size of path" << path.size() << endl;
 //
 //     //debugging
 //     // for (auto & edge : path) {
 //     //   cout << edge.source << " " << edge.dest << endl;
 //     // }
 //
 //     return path;
 //   }
 //   else {
 //     Vertex src2 = "p2-" + to_string(diff); //this source is the same as p1's dest
 //     Vertex dest2 = "p1-" + to_string(diff2);
 //     path.push_back(g_.getEdge(src2,dest2));
 //     i = diff2+1; //add one because for loop subtracts every iteration
 //   }
 // }
 //
 // // //debugging
 // // for (auto & edge : path) {
 // //   cout << edge.source << " " << edge.dest << endl;
 // // }
 //
 //  return path;



  unsigned player = 1;
  int cur;
  if (startingVertex_ == "p1-10") cur = 10;
  else cur = (int)startingVertex_[3] - '0';
  while (cur > 1) {
    unsigned next = cur - (rand() % 2 + 1);
    Vertex s = "p" + to_string(player) + "-" + to_string(cur);
    if (player == 2) {
      player = 1;
    } else {
      player = 2;
    }
    Vertex e = "p" + to_string(player) + "-" + to_string(next);
    path.push_back(g_.getEdge(s, e));
    cur = next;
  }
  if (cur == 1) {
    Vertex s = "p" + to_string(player) + "-" + to_string(cur);
    if (player == 2) {
      player = 1;
    } else {
      player = 2;
    }
    Vertex e = "p" + to_string(player) + "-" + to_string(0);
    path.push_back(g_.getEdge(s, e));
  }
  return path;




}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 // int cur;
 // if (startingVertex_ == "p1-10") cur = 10;
 // else cur = (int)startingVertex_[3] - '0';
 //
 // if (cur == 1)  {
 //   g_.setEdgeWeight("p1-1", "p2-0", g_.getEdgeWeight("p1-1","p2-0")+1);
 //   return;
 // }
 //
 // bool p1wins = false;
 // // cout << path[path.size()-1].dest << endl;
 // if (path[path.size()-1].dest == "p2-0") { //player 1 wins
 //   // cout << "p1 wins" << endl;
 //   bool p1wins = true;
 // }
 //
 // for (auto & edge : path)  {
 //     Vertex src = edge.source;
 //     // cout << "src: " << src << endl;
 //     Vertex dest = edge.dest;
 //     // cout << "dest: " << dest << endl;
 //     if (src[1] == '1') { //player 1 move
 //       // cout << "p1 move being rewarded" << endl;
 //       if (p1wins) g_.setEdgeWeight(src, dest, g_.getEdgeWeight(src,dest)+1); //reward
 //       else g_.setEdgeWeight(src, dest, g_.getEdgeWeight(src,dest)-1); //punish
 //     }
 //     else { //player 2 move
 //       if (p1wins) g_.setEdgeWeight(src, dest, g_.getEdgeWeight(src,dest)-1); //punish
 //       else g_.setEdgeWeight(src, dest, g_.getEdgeWeight(src,dest)+1); //reward
 //     }
 //   }
 //
 //   cout << "p1-3, p2-2: " << g_.getEdgeWeight( "p1-3", "p2-2") << endl;
 //   cout << "p1-3, p2-1: " << g_.getEdgeWeight( "p1-3", "p2-1") << endl;
 //

   bool p1wins = false;
   if (path[path.size()-1].dest == "p2-0") { //player 1 wins
     bool p1wins = true;
   }

   if (p1wins) { //p1 winner.
     int reward = -1;
     for (unsigned i = 0; i < path.size(); i++) {
       Vertex v1 = path[i].source;
       Vertex v2 = path[i].dest;
       int weight = g_.getEdgeWeight(v1, v2) + reward;
       g_.setEdgeWeight(v1, v2, weight);
       reward = -reward;
     }
   }
   else { //p2 winner
     int reward = 1;
     for (unsigned i = 0; i < path.size(); i++) {

       if (path[i].source == "p2-2" || path[i].source == "p2-1") {
         int weight = g_.getEdgeWeight(path[i].source, path[i].dest) + 2;
         g_.setEdgeWeight(path[i].source, path[i].dest, weight);
       }

       Vertex v1 = path[i].source;
       Vertex v2 = path[i].dest;
       // cout << "Adding " << reward << "to edge: " << v1 << v2 << endl;
       int weight = g_.getEdgeWeight(v1, v2) + reward;
       g_.setEdgeWeight(v1, v2, weight);
       reward = -reward;
     }
   }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
