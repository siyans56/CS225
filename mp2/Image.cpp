#include "Image.h"
#include "cs225/PNG.h"


void Image::lighten() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

    HSLAPixel & pixel = this->getPixel(x, y);
    if (pixel.l + .1 > 1) {
      pixel.l = 1;
    }
    else {
      pixel.l+=.1;
      }
    }
  }
}
void Image::lighten(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

    HSLAPixel & pixel = this->getPixel(x, y);
    if (pixel.l + amount > 1) {
      pixel.l = 1;
    }
    else {
      pixel.l+=amount;
      }
    }
  }
}

void Image::darken(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

    HSLAPixel & pixel = this->getPixel(x, y);
    if (pixel.l - .1 < 1) {
      pixel.l = 0;
    }
    else {
      pixel.l-=.1;
      }
    }
  }
}
void Image::darken(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

    HSLAPixel & pixel = this->getPixel(x, y);
    if (pixel.l - amount < 0) {
      pixel.l = 0;
    }
    else {
      pixel.l-=amount;
      }
    }
  }
}

void Image::saturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

    HSLAPixel & pixel = this->getPixel(x, y);
    if (pixel.s + .1 > 1) {
      pixel.s = 1;
    }
    else {
      pixel.s+=.1;
      }
    }
  }
}
void Image::saturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

    HSLAPixel & pixel = this->getPixel(x, y);
    if (pixel.s + amount > 1) {
      pixel.s = 1;
    }
    else {
      pixel.s+=amount;
      }
    }
  }
}

void Image::desaturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

    HSLAPixel & pixel = this->getPixel(x, y);
    if (pixel.s - .1 < 1) {
      pixel.s = 0;
    }
    else {
      pixel.s-=.1;
      }
    }
  }
}
void Image::desaturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

    HSLAPixel & pixel = this->getPixel(x, y);
    if (pixel.s - amount < 1) {
      pixel.s = 0;
    }
    else {
      pixel.s-=amount;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
//wraparound needs to be added
for (unsigned x = 0; x < this->width(); x++) {
  for (unsigned y = 0; y < this->height(); y++) {

  HSLAPixel & pixel = this->getPixel(x, y);
  if (degrees < 0) {degrees = 360+degrees;}
  pixel.h+=degrees;
  if (pixel.h > 360) {pixel.h = pixel.h - 360;}
/*    for (int i = 0; i < degrees; i++) {
     if (pixel.h++ > 360) {
        pixel.h = 0;
      } else {
          pixel.h++;
        }
      }*/
    }
  }
}


void Image::illinify(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if (pixel.h > 113.5 && pixel.h < 293) {
        pixel.h = 216;
      }
      else {
        pixel.h = 11;
      }
    }
  }
}

void Image::scale(double factor){
//get ratio, then maintain it by factor
//create new image, then copy BACK into this image after changing width and height
  if (factor != 1) {
    //Getting width and height of new image scale
    int scalewidth = this->width();
    scalewidth = scalewidth*factor;
    int scaleheight = this->height();
    scaleheight = scaleheight*factor;

    PNG scaleimg = PNG::PNG(scalewidth,scaleheight); //create new PNG with scaled size

    //Iterate through both new and old images and assign pixels to new
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
        HSLAPixel & pixel = this->getPixel(x, y); //switc which is being iterated by factor for increase and decrease
        HSLAPixel & scalepixel = scaleimg.getPixel((int)(x*factor), (int)(y*factor)); //iterate thru scaled group
        scalepixel.h = pixel.h;
        scalepixel.s = pixel.s;
        scalepixel.l = pixel.l;
        scalepixel.a = pixel.a;

      }
    }
    this->resize(scalewidth,scaleheight); //resize to new scaled size. DOES NOT ALTER PIXELS, JUST BORDER
//need to put back into new image
//DOES RESIZE EXPAND IN ALL DIRECTIONS OR IS IT ANCHORED?
    for (unsigned x = 0; x < scaleimg.width(); x++) {
      for (unsigned y = 0; y < scaleimg.height(); y++) {
        HSLAPixel & scaleimgpixel = scaleimg.getPixel(x, y);
        HSLAPixel & newimg = this->getPixel(x,y); //iterate thru scaled group
        newimg.h = scaleimgpixel.h;
        newimg.s = scaleimgpixel.s;
        newimg.l = scaleimgpixel.l;
        newimg.a = scaleimgpixel.a;

        }
      }
    }
  }

void Image::scale(unsigned w, unsigned h){
//get ration, then maintain it by amount only need height or width? smaller or larger of two
//900x600, scale to 300x300. ratio is 3:2 originally, so now do scale function on one

  if (this->width() == w && this->height() == h) {return;} //if same size, no change

  if (w>=h) { //if image is wider or square
    double factor = h/this->height();
    this->scale(factor); //image is now correct height, but needs to fill width

    PNG scaleimg = PNG::PNG(w,h);
    double ratio = w/this->width();
    for (unsigned x = 0; x < this->width(); x++) { //600
      for (unsigned y = 0; y < this->height(); y++) { //300
        HSLAPixel & pixel = this->getPixel(x, y); //switch which is being iterated by factor for increase and decrease
        HSLAPixel & scalepixel = scaleimg.getPixel((int)(x*ratio), y); //iterate thru scaled group, only width is different b/w two images
        scalepixel.h = pixel.h;
        scalepixel.s = pixel.s;
        scalepixel.l = pixel.l;
        scalepixel.a = pixel.a;

      }
    }
    this->resize(w,h);
  }
  if (w<h) {
    double factor = w/this->width();
    this->scale(factor); //image is now correct width, but needs to fill height

    PNG scaleimg = PNG::PNG(w,h);
    double ratio = h/this->height();
    for (unsigned x = 0; x < this->width(); x++) { //600
      for (unsigned y = 0; y < this->height(); y++) { //300
        HSLAPixel & pixel = this->getPixel(x, y); //switch which is being iterated by factor for increase and decrease
        HSLAPixel & scalepixel = scaleimg.getPixel(x, (int)(y*ratio)); //iterate thru scaled group, only height is different b/w two images
        scalepixel.h = pixel.h;
        scalepixel.s = pixel.s;
        scalepixel.l = pixel.l;
        scalepixel.a = pixel.a;

      }
    }
    this->resize(w,h);


  }

return;
}
