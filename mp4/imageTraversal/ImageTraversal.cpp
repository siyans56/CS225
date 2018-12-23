#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

bool ImageTraversal::checkValid(Point next) {
  if (next.x < pic_->width() && next.y < pic_->height()) {
    HSLAPixel* startpixel = &(pic_->getPixel(start_.x, start_.y));
    HSLAPixel* nextpixel = &(pic_->getPixel(next.x, next.y));
    if (calculateDelta(*startpixel, *nextpixel) < tolerance_) {
      //std::cout<<"Valid"<<std::endl;
      return true;}
    }
  //std::cout<<"Invalid"<<std::endl;
  return false;
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  //size_ = 0;
  //visited_ = new bool[size_];
  //size_ = 0;
  loc_ = Point(0,0);
  it_ = NULL;
  visited_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* imaget) {
  int h = imaget->pic_->height();
  int w = imaget->pic_->width();
  visited_ = new bool[h * w];
  for( int i = 0; i < h * w; ++i ){
    visited_[ i ] = false;
  }
  visited_[imaget->start_.y * imaget->pic_->width() + imaget->start_.x] = true;
  it_ = imaget;
  loc_ = imaget->start_;

  /*visited_ = new bool[h][w];
  for (unsigned y = 0; y < imaget->pic_->height(); y++) {
    for (unsigned x = 0; x; x < imaget->pic_->width(); x++) {
      visited_[y][x] = false;
    }
  }*/
  //size_ = h * w;
  //visited_[loc_.y][loc_.x] = true;
  it_->pop();
  //initial adding of neighbors
  Point toadd = loc_;
  Point check1 = Point(toadd.x + 1, toadd.y);
  Point check2 = Point(toadd.x, toadd.y + 1);
  Point check3 = Point(toadd.x - 1, toadd.y);
  Point check4 = Point(toadd.x, toadd.y - 1);
  if (it_->checkValid(check1)) {
    //std::cout<<"Adding x+1 (1/4)"<<std::endl;
    it_->add(check1);}
  if (it_->checkValid(check2)) {
    //std::cout<<"Adding y+1 (2/4)"<<std::endl;
    it_->add(check2);}
  if (it_->checkValid(check3)) {
    //std::cout<<"Adding x-1 (3/4)"<<std::endl;
    it_->add(check3);}
  if (it_->checkValid(check4)) {
    //std::cout<<"Adding y-1 (4/4)"<<std::endl;
    it_->add(check4);}
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //first need next point to save as loc_, then need to scan its neighbors
  Point toadd = it_->peek(); //check next item in stack/queue
  //std::cout<<"Current: "<<loc_.x<<" "<<loc_.y<<std::endl;
  while (visited_[toadd.y * it_->pic_->width() + toadd.x] == true) { //get next not visited point
    //std::cout<<"Already visited "<<toadd.x<<" "<<toadd.y<<std::endl;
    it_->pop(); //discard already visited
    toadd = it_->peek(); //check next in line
    if (toadd == it_->start_ && it_->empty()) { //if empty stack/queue and at start
      loc_ = Point(0,0);
      it_ = NULL;
      return *this;
    }
  }
  loc_ = toadd; //set it to next unvisited
  //visited_[loc_.y][loc_.x] = true;
  visited_[loc_.y * it_->pic_->width() + loc_.x] = true;
  //std::cout<<"New: "<<loc_.x<<" "<<loc_.y<<std::endl;
  if (toadd == it_->start_ && it_->empty()) { //if empty stack/queue and at start
    loc_ = Point(0,0);
    it_ = NULL;
    return *this;
  }

  /*
  if (toadd.visited == FALSE) {
    nextPoint = it_->pop();
    wasvisited = visited_[nextPoint.y * it_->pic_->width() + nextPoint.x];
    if (nextPoint == it_->start_ && it_->empty()) {
      loc_ = Point(0,0);
      it_ = NULL;
      return *this;
    }
  }*/
  Point nextup = loc_;
  Point check1 = Point(nextup.x + 1, nextup.y);
  Point check2 = Point(nextup.x, nextup.y + 1);
  Point check3 = Point(nextup.x - 1, nextup.y);
  Point check4 = Point(nextup.x, nextup.y - 1);
  if (it_->checkValid(check1)) {
    //std::cout<<"Adding x+1 (1/4)"<<std::endl;
    it_->add(check1);}
  if (it_->checkValid(check2)) {
    //std::cout<<"Adding y+1 (2/4)"<<std::endl;
    it_->add(check2);}
  if (it_->checkValid(check3)) {
    //std::cout<<"Adding x-1 (3/4)"<<std::endl;
    it_->add(check3);}
  if (it_->checkValid(check4)) {
    //std::cout<<"Adding y-1 (4/4)"<<std::endl;
    it_->add(check4);}

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return loc_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (loc_ == other.loc_ && it_ == other.it_) {return false;}
  return true;
}
