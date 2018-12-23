#include <iostream>
#include "maze.h"
#include <queue>
#include <map>
#include <math.h>
#include <unordered_map>
#include "dsets.h"
using namespace std;

SquareMaze::SquareMaze() {
  w_ = 0;
  h_ = 0;
  return;
}

/**
 * Makes a new SquareMaze of the given height and width.
 */

//  Makes a new SquareMaze of the given height and width.
//
// If this object already represents a maze it will clear all the existing data
// before doing so. You will start with a square grid (like graph paper)
//  with the specified height and width. You will select random walls to delete
//  without creating a cycle, until there are no more walls that could be deleted
//   without creating a cycle. Do not delete walls on the perimeter of the grid.
//
// Hints: You only need to store 2 bits per square: the "down" and "right" walls.
// The finished maze is always a tree of corridors.)

// Parameters
// width	The width of the SquareMaze (number of cells)
// height	The height of the SquareMaze (number of cells)

void SquareMaze::makeMaze(int width, int height) {
  walls_.clear(); //clear old maze
  w_ = width;
  h_ = height;

  //initially creates a mazo with all the walls up
  for (int i = 0; i < width*height; i++) {
    walls_.push_back(std::make_pair(true,true));
  }

  DisjointSets set;
  set.addelements(w_*h_);
  int i = 0;

  while (i < w_ * h_ - 1) {
    int x = rand() % w_; //generate random x
    int y = rand() % h_; //generate randm y
    int dir = rand() % 2; //generate random dir (0 or 1)


    if (dir == 1 && y != (h_ - 1)) { //if we are looking at the bottom wall and are not at the bottom row
      if (walls_[y * w_ + x].second == true) { //if the bottom wall exists
        if (set.find(y * w_ + x) != set.find((y + 1) * w_ + x)) { //if cell below are separated
          walls_[y * w_ + x].second = false; //can remove wall
          set.setunion(y * w_ + x, (y + 1) * w_ + x); //add together the sets
          i++;
        }
      }
    }
    if (dir == 0 && x != (w_ - 1)) { //if we are looking right and are not at the right edge
      if (walls_[y * w_ + x].first == true) { //if the wall to the right exists
        if (set.find(y * w_ + x) != set.find(y * w_ + x + 1)) { //if cell to the right is separated
          walls_[y * w_ + x].first = false; //can remove
          set.setunion(y * w_ + x, y * w_ + x + 1); //add together the sets
          i++;
        }
      }
    }
  }
}


// // dir = 0 represents a rightward step (+1 to the x coordinate)
// // dir = 1 represents a downward step (+1 to the y coordinate)
// // dir = 2 represents a leftward step (-1 to the x coordinate)
// // dir = 3 represents an upward step (-1 to the y coordinate)
// // You can not step off of the maze or through a wall.
// //
// This function will be very helpful in solving the maze.
// It will also be used by the grading program to verify that your maze is a tree
// that occupies the whole grid, and to verify your maze solution.
// So make sure that this function works!
// //
// // Parameters:
// // x	The x coordinate of the current cell
// // y	The y coordinate of the current cell
// // dir	The desired direction to move from the current cell
// // Returns: whether you can travel in the specified direction
bool SquareMaze::canTravel(int x, int y, int dir) const {
  // FIRST: Check if out of maze bounds
  // SECOND: Check if wall is blocking
  if (x >= w_ || y >= h_) return false;
  switch (dir) { //case is what dir equals to
    case 0:
    {
      if (x + 1 >= w_) return false; //if x+1 is outside of bounds, return false
      if (walls_[y * w_ + x].first) return false; //wall in the way
      return true;
    }
    case 1:
    {
      if (y + 1 >= h_) return false; //if y+1 is outside of bounds, return false
      if (walls_[y * w_ + x].second) return false; //wall in the way
      return true;
    }
    case 2:
    {
      if (x - 1 < 0) return false; //if x-1 is outside of bounds, return false
      //since we only track right and bottom, check the cell to the left's right
      if (walls_[y * w_ + (x-1)].first) return false; //wall in the way
      return true;
    }
    case 3:
    {
      if (y - 1 < 0) return false; //if y-1 is outside of bounds, return false
      //since we only track right and bottom, check the cell above's bottom
      if (walls_[(y - 1) * w_ + x].second) return false; //wall in the way
      return true;
    }
  }
  return true; //just in case
}

// Sets whether or not the specified wall exists.
//
// This function should be fast (constant time). You can assume that in grading we
// will not make your maze a non-tree and then call one of the other member functions.
// setWall should not prevent cycles from occurring, but should simply set a wall to
// be present or not present. Our tests will call setWall to copy a specific maze into your implementation.
//
// Parameters
// x:	The x coordinate of the current cell
// y:	The y coordinate of the current cell
// dir:	Either 0 (right) or 1 (down), which specifies which wall to set
// (same as the encoding explained in canTravel). You only need to support setting
// the bottom and right walls of every square in the grid.
// exists:	true if setting the wall to exist, false otherwise
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  //not sure if we should be checking if valid cell/wall, just in case tho...
  if (x >= w_ || y >= h_) return;

  //actual work: set or remove the wall as requested
  if (exists) { //set a wall
    if (dir == 0) { //right wall
      walls_[y*w_ + x].first = true;
    }
    else walls_[y*w_ + x].second = true; //lower wall
  }
  else { //remove the wall
    if (dir == 0) { //right wall
      walls_[y*w_ + x].first = false;
    }
    else walls_[y*w_ + x].second = false; //lower wall
  }
}

// Solves this SquareMaze.
//
// For each square on the bottom row (maximum y coordinate), there is a distance
// from the origin (i.e. the top-left cell), which is defined as the length
// (measured as a number of steps) of the only path through the maze from the origin to that square.
//
// Select the square in the bottom row with the largest distance from the origin as
//  the destination of the maze. solveMaze() returns the winning path from the
//  origin to the destination as a vector of integers, where each integer represents
//   the direction of a step, using the same encoding as in canTravel().
//
// If multiple paths of maximum length exist, use the one with the destination
// cell that has the smallest x value.
//
// Hint: this function should run in time linear in the number of cells in the maze.
//
// Returns
// a vector of directions taken to solve the maze
vector<int> SquareMaze::solveMaze() {
  // return vector<int>();
  vector<int> sol; //solution vector
  vector<int> temp; //used in between for finding each destination solutoin
  unordered_map<int, int> set_map; //map to hold a cell and its previous that can travel into it
  queue<int> next; //queue for BFS traversal
  int dist = 0; //checking how long each solution is
  int max = 0; //for checking which solution is longest
  vector<bool> visited;  //( w_ * h_ , false); //keep track of visited cells
  for (int i = 0; i < w_*h_; i++) {
    visited.push_back(false);
  }
  //call BFS traversal on bottom row to find max distance destination

  // dir = 0 represents a rightward step (+1 to the x coordinate)
  // dir = 1 represents a downward step (+1 to the y coordinate)
  // dir = 2 represents a leftward step (-1 to the x coordinate)
  // dir = 3 represents an upward step (-1 to the y coordinate)

  //start at the first point, check cantravel, set map, push next, pop until done

  next.push(0); //star thte BFS


  while (!next.empty()) {
    int cur = next.front();
    next.pop();
    int x = cur % w_;
    int y = cur / w_;
    //y = cur / w, x = cur % w
    if (canTravel(x, y , 0)) {
      if (!visited[cur + 1]) { //can travel right
        //set the right cell to this value
          set_map[(y) * w_ + ((x) + 1)] = cur;
        next.push((y) * w_ + ((x) + 1));
        // visited[(x) * w_ + ((y) + 1)] = true; //mark as visited
        visited[cur + 1] = true;
      }
    }
    if (canTravel(x, y , 1)) { //can travel down
      if (!visited[cur + w_]) {
        //set the below cell to this value
          set_map[((y) + 1) * w_ + (x)] = cur;
        next.push(((y) + 1) * w_ + (x));
        // visited[((x) + 1) * w_ + (y)] = true;
        visited[cur + w_] = true;
      }
    }
    if (canTravel(x, y , 2)) { //can travel left
      if (!visited[cur - 1]) {
        //set the left cell to this value
          set_map[(y) * w_ + ((x) - 1)] = cur;
        next.push((y) * w_ + ((x) - 1));
        // visited[(x) * w_ + ((y) - 1)] = true;
        visited[cur - 1] = true;
      }
    }
    if (canTravel(x, y , 3)) { //can travel up
      if (!visited[cur - w_]) {
        //set the upper cell to this value
          set_map[((y) - 1) * w_ + (x)] = cur;
        next.push(((y) - 1) * w_ + (x));
        // visited[((x) - 1) * w_ + (y)] = true;
        visited[cur - w_] = true;
      }
    }
  }

  //iterate thru bottom row, go thru map and see if i can reach the start point
  //store size along the way,
  //sol vector insert at front

  for (int x = 0; x < w_; x++) {
    int check = (h_ - 1) * w_ + x; //checking last row only
    vector<int> temp; //used in between for finding each destination solutoin

    while (check != 0) { //run until we reach the start point
      int cur = check; //current coord
      int prev = set_map[check]; //previous coord
      int diff = cur-prev;

      if (diff == 1) temp.insert(temp.begin(), 0); //cur is to the right of prev, so you want to move right
      if (diff == w_) temp.insert(temp.begin(), 1);  //cur is below prev, so you want to move down
      if (diff == -1) temp.insert(temp.begin(), 2); //cur is to the left of prev, so you want to move left
      if (diff == (w_)*-1) temp.insert(temp.begin(), 3); //cur is above prev, so you want to move up

      check = prev; //look at next item in set
      dist++; //tracking distance
    }

    if (temp.size() > sol.size()) { //store the largest destination maze/distance.
      //will only overwrite if larger max distance, so if multiple same
      //length paths, preivous one is automatically kept
      sol = temp; //set solution vector
      max = dist; //set max distance checker
    }
  }

  return sol;
}

// Draws the maze without the solution.
//
// First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1).
// where height and width were the arguments to makeMaze. Blacken the entire topmost
// row and leftmost column of pixels, except the entrance (1,0) through (9,0).
// For each square in the maze, call its maze coordinates (x,y).
//  If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10.
//  If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
//
// The resulting PNG will look like the sample image, except there will be no exit
//  from the maze and the red line will be missing.
//
// Returns
// a PNG of the unsolved SquareMaze
cs225::PNG* SquareMaze::drawMaze() const {
  //define the image frame
  cs225::PNG* p = new cs225::PNG(w_*10+1,h_*10+1);
  cs225::HSLAPixel black(0, 0, 0); //black pixel to use for darkening

  //TODO: blacken the leftmost column and top row except 1,0 thru 9,0
  for (int i = 10; i < w_*10+1; i++) {
    cs225::HSLAPixel* pix = &(p->getPixel(i,0));
    pix->h = 0;
    pix->s = 0;
    pix->l = 0;
    pix->a = 1;
  }

  for (int j = 0; j < h_*10+1; j++) {
    cs225::HSLAPixel* pix = &(p->getPixel(0,j));
    pix->h = 0;
    pix->s = 0;
    pix->l = 0;
    pix->a = 1;
  }

  //TODO: iteratue thru and call the maze coords to fill the walls in
  for (int i = 0; i < w_; i++) {
    for (int j = 0; j < h_; j++) {
      if (walls_[j*w_+i].first == true) { //need to make right wall
        for (int k = 0; k <= 10; k++) { //iterate thru vertically from toprightmost pix
          cs225::HSLAPixel* pix = &(p->getPixel((i+1)*10,j*10+k));
          pix->h = 0;
          pix->s = 0;
          pix->l = 0;
          pix->a = 1;
        }
      }
      if (walls_[j*w_+i].second == true) { //need to make the lower wall
        for (int k = 0; k <= 10; k++) { //iterate thru horizontally from bottomleftmost pix
          cs225::HSLAPixel* pix = &(p->getPixel(i*10+k,(j+1)*10));
          pix->h = 0;
          pix->s = 0;
          pix->l = 0;
          pix->a = 1;
        }
      }
    }
  }
  return p;

}

// This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze
// to show the solution vector and the exit.
//
// Start at pixel (5,5). Each direction in the solution vector corresponds to a
// trail of 11 red pixels in the given direction. If the first step is downward,
// color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA).
// Then if the second step is right, color pixels (5,15) through (15,15) red.
// Then if the third step is up, color pixels (15,15) through (15,5) red.
// Continue in this manner until you get to the end of the solution vector,
// so that your output looks analogous the above picture.
//
// Make the exit by undoing the bottom wall of the destination square: call the
// destination maze coordinates (x,y), and whiten the pixels with coordinates
// (x*10+k, (y+1)*10) for k from 1 to 9.
//
// Returns
// a PNG of the solved SquareMaze
// REMINDER:
// dir = 0 represents a rightward step (+1 to the x coordinate)
// dir = 1 represents a downward step (+1 to the y coordinate)
// dir = 2 represents a leftward step (-1 to the x coordinate)
// dir = 3 represents an upward step (-1 to the y coordinate)

cs225::PNG* SquareMaze::drawMazeWithSolution() {
  cs225::PNG* p = this->drawMaze(); //draw basic outline and the walls
  std::vector<int> sol = this->solveMaze();

  int x = 0, y = 0; //keep track of current cell. After done with solution
  //it should be at the destination cell

//TODO: Go through solution vector and draw the corresponding directions per cell
  cs225::HSLAPixel* pix = &(p->getPixel(5,5));
  pix->h = 0;
  pix->s = 1;
  pix->l = 0.5;
  pix->a = 1;

  for (auto & step: sol) { //iteration thru the solution
    switch (step) { //case is what dir equals to
      case 0: //need to draw a right line
      {
        for (int i = -5; i <= 5; i++) { //drawing 11 pixels across two cells
          cs225::HSLAPixel* pix = &(p->getPixel(x*10+i,y*10+5));
          pix->h = 0;
          pix->s = 1;
          pix->l = 0.5;
          pix->a = 1;
        x++; //moving right
        break;
      }
      case 1: //need to draw a downward line
      {
        for (int i = -5; i <= 5; i++) { //drawing 11 pixels
          cs225::HSLAPixel* pix = &(p->getPixel(x*10+5,y*10+i));
          pix->h = 0;
          pix->s = 1;
          pix->l = 0.5;
          pix->a = 1;
        }
        y++; //moving down
        break;
      }
      case 2: //need to draw a leftward line
      {
        for (int i = -5; i <= 5; i++) { //drawing 11 pixels
          cs225::HSLAPixel* pix = &(p->getPixel(x*10+i,y*10+5));
          pix->h = 0;
          pix->s = 1;
          pix->l = 0.5;
          pix->a = 1;
        }
        y--; //moving left
        break;
      }
      case 3: //need to draw a upward line
      {
        for (int i = -5; i <= 5; i++) { //drawing 11 pixels
          cs225::HSLAPixel* pix = &(p->getPixel(x*10+5,y*10+i));
          pix->h = 0;
          pix->s = 1;
          pix->l = 0.5;
          pix->a = 1;
        }
        x--; //moving up
        break;
      }
    }
  }
//TODO: Whiten out the exit and undo the bottom wall of the destination
  for (int k = 1; k < 10; k++) {
    cs225::HSLAPixel* pix = &(p->getPixel(x*10+k,(y+1)*10));
    pix->h = 0;
    pix->s = 0;
    pix->l = 1;
    pix->a = 1;
  }
}
  return p;
}
