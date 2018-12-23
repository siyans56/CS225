#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG image;
  image.readFromFile(inputFile);
  PNG rotimage(image.width(),image.height());
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
    HSLAPixel & pixel = image.getPixel(x, y);
    HSLAPixel & rotatepixel = rotimage.getPixel((image.width()-1)-x,(image.height()-1)-y);
    // `pixel` is a pointer to the memory stored inside of the PNG `image`,
    // which means you're changing the image directly.  No need to `set`
    // the pixel since you're directly changing the memory of the image.
    rotatepixel.h = pixel.h;
    rotatepixel.s = pixel.s;
    rotatepixel.l = pixel.l;
    rotatepixel.a = pixel.a;
    }
  }
    rotimage.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
 PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
    HSLAPixel & pixel = png.getPixel(x, y);
    if (x <= 200) {
      pixel.h = rand() % 60;
    }
    else if (y <=200) {
      pixel.h = rand() % 120;
    }
    else if (x >=600) {
      pixel.h = rand() % 180;
    }
    else if (y >=600) {
      pixel.h = rand() % 240;
    }
    else if (x <=400) {
      pixel.h = rand() % 320;
    }
    else pixel.h = rand() % 360;
    pixel.s = 1;
    pixel.l = .5;//(rand() % 100)/100;
    pixel.a = 1;
    }
  }

  return png;
}
