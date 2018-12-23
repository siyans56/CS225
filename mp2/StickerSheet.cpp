#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>
//make sure everything is null, arrmax bounds, parenthesis around logic,
StickerSheet::StickerSheet(const Image & picture, unsigned max) {
  arrmax = max+1;
//  basepic = picture;
  imgar = new Image[arrmax]; //array of Image
  for (unsigned i = 0; i < max; i++) {
    imgar[i] = blank;
  }
  imgar[0] = picture;

  xarr = new unsigned[arrmax];
  for (unsigned i = 0; i < max; i++) {
    xarr[i] = 0;
  }
  //xarr[0] = NULL;

  yarr = new unsigned[arrmax];
  for (unsigned i = 0; i < max; i++) {
    yarr[i] = 0;
  }
  //yarr[0] = NULL;
  test = "String Created , size : " + std::to_string(arrmax);
}

StickerSheet::~StickerSheet() {
  if (imgar != NULL) {
  delete[] imgar;
  }
  imgar = NULL;

  if (xarr != NULL) {
  delete[] xarr;
  }
  xarr = NULL;

  if (yarr != NULL) {
  delete[] yarr;
  }
  yarr = NULL;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
  arrmax = other.arrmax;
  xarr = new unsigned[other.arrmax];
  yarr = new unsigned[other.arrmax];
  imgar = new Image[other.arrmax];
  for (unsigned i = 0; i < other.arrmax; i++) {
    imgar[i] = other.imgar[i];
    xarr[i] = other.xarr[i];
    yarr[i] = other.yarr[i];
  }

}

const StickerSheet & StickerSheet::operator= (const StickerSheet & other) {

  if (imgar != NULL) {
    delete[] imgar;
  }
  if (xarr != NULL) {
    delete[] xarr;
  }
  if (yarr != NULL) {
    delete[] yarr;
  }

  arrmax = other.arrmax;
  imgar = new Image[arrmax];
  xarr = new unsigned[arrmax];
  yarr = new unsigned[arrmax];
  for (unsigned i = 0; i < arrmax; i++) {
    imgar[i] = other.imgar[i];
    xarr[i] = other.xarr[i];
    yarr[i] = other.yarr[i];
  }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  Image* temp = new Image[max+1]; //temporary array of images with all stickers AND BASE
  unsigned* tempx = new unsigned[max+1];
  unsigned* tempy = new unsigned[max+1];

  if (max == arrmax+1) {return;}

  if (max < arrmax+1) { //if new max sticker is smaller than original array
    for (unsigned i = 0; i <= max; i++) { //only copy over defined values that fit in new array
      temp[i] = imgar[i];
      tempx[i] = xarr[i];
      tempy[i] = yarr[i];
    }
  }
  else {
    for (unsigned i = 0; i < arrmax; i++) { //only copy over defined values from original array
      temp[i] = imgar[i];
      tempx[i] = xarr[i];
      tempy[i] = yarr[i];
    }
    for (unsigned i = arrmax; i < max; i++) { //populate other elements to NULL
      temp[i] = blank;
      tempx[i] = 0;
      tempy[i] = 0;
    }
  }
  if (imgar != NULL) {delete[] imgar;}
  if (xarr != NULL) {delete[] xarr;}
  if (yarr != NULL) {delete[] yarr;}
  arrmax = max;
  imgar = temp; //do i have to reinitialize?
  xarr = tempx;
  yarr = tempy;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
  if (imgar[arrmax-1] == blank) { //if there is space in stickersheet
    for (unsigned i = 0; i < arrmax; i++) {
      if (imgar[i] == blank) {
        imgar[i] = sticker;
        xarr[i] = x;
        yarr[i] = y;
        return i;
      }
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index >= arrmax || imgar[index+1] == blank) {return false;}
  else {
    xarr[index+1] = x;
    yarr[index+1] = y;
    return true;
  }
}

void StickerSheet::removeSticker(unsigned index) {
  if (index < arrmax) {
    imgar[index+1] = blank;
    xarr[index+1] = 0;
    yarr[index+1] = 0;
  }
  return;
}

Image * StickerSheet::getSticker(unsigned index) const {
  if (index >= arrmax || imgar[index+1] == blank) {return NULL;}
  Image* requested = &imgar[index+1];
  return requested;
}

Image StickerSheet::render() const {
  /*


Renders the whole StickerSheet on one Image and returns that Image.

The base picture is drawn first and then each sticker is drawn in order starting with layer zero (0), then layer one (1), and so on.

If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that sticker at that pixel.
 If the alpha channel is non-zero, a pixel is drawn. (Alpha blending is awesome, but not required.)

The returned Image always includes the full contents of the picture and all stickers.
This means that the size of the result image may be larger than the base picture if some stickers go beyond the edge of the picture.

Returns an Image object representing the drawn scene

MY THOUGHTS:
Iterate through base, create image
Then, add sticker one by one
Check bounds for image

  */

//Start by drawing the basepic

//First, resize picture to account for StickerSheet. then copy

//Image* drawing = new Image;
//*drawing = imgar[0]; //canvas now contains base image (and dimensions)
Image drawing = imgar[0];
//get bounds, have to draw when inside the bounds of the sticker itself
for (unsigned i = 1; i < arrmax; i++) { //iterate through the stickersheet Array
  if (imgar[i] != blank) {

//  Image tocopy = imgar[i]; //temp image contining current sticker to be drawn
  unsigned int xdistance = xarr[i]+imgar[i].width();
  unsigned int ydistance = yarr[i]+imgar[i].height();
  if ((xdistance > drawing.width()) || (ydistance > drawing.height())) { //If sticker goes off the edge of base
   double xfactor = (xdistance / drawing.width());
   double yfactor = (ydistance / drawing.height());
    if (xfactor > yfactor) {drawing.scale(xfactor);} //resize to larger edge
    else {drawing.scale(yfactor);}

  }

  for (unsigned x = 0; x < imgar[i].width(); x++) { //iterate thru sticker width
    for (unsigned y = 0; y < imgar[i].height(); y++) { //iterate thru sticker height
  //    if (x >= tocopy.xloc && x < tocopy.xloc + tocopy.width() && y >= tocopy.yloc && y < tocopy.yloc + tocopy.height()) { //If we are looking at pixels that contain the sticker
        HSLAPixel & pixel = drawing.getPixel(x+xarr[i], y+yarr[i]); //get pixel of the drawing
        HSLAPixel & tocopypixel = imgar[i].getPixel(x,y); //get pixel of the sticker
          if (pixel.a != 0) { //if pixel actually has color
            pixel.h = tocopypixel.h; //set the pixels of the base drawing to the new sticker's pixels
            pixel.s = tocopypixel.s;
            pixel.l = tocopypixel.l;
            pixel.a = tocopypixel.a;
          }
        }
      }
    }
  }
return drawing;
}
