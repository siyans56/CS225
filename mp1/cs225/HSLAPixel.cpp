/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  HSLAPixel::HSLAPixel() {
    a = 1;
    l = 1;
  }
  HSLAPixel::HSLAPixel(double hue,double saturation, double lumination) {
    a = 1;
    h = hue;
    s = saturation;
    l = lumination;
  }
  HSLAPixel::HSLAPixel(double hue, double saturation, double lumination, double alpha) {
    h = hue;
    s = saturation;
    l = lumination;
    a = alpha;
  }
}
