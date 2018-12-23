#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  png_ = png;

}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  //push to queue the pair
  //auto p = std::make_pair(&traversal, &colorPicker);
  itv_.push_back(&traversal);
  cpv_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */

  int intervalcount = 0;
  animation.addFrame(png_); //capture first frame
  for (unsigned i = 0; i < itv_.size(); i++) { //go through the q and do floodfills
    //auto curr = q_.front();
    //q_.pop();
    ImageTraversal* imaget = itv_[i]; //.front();// curr.first; //assign current ImageTraversal
    ColorPicker* colpick = cpv_[i];//front();//curr.second; //assign current ColorPicker

    for (ImageTraversal::Iterator it = imaget->begin(); it != imaget->end(); ++it) {
      int x = (*it).x;
      int y = (*it).y;
      HSLAPixel* pix = &(png_.getPixel(x,y)); //original pixel
      HSLAPixel newpix = colpick->getColor(x,y); //change made by colorpicker
      *pix = newpix; //assign as new pixel

      intervalcount++;
      if (intervalcount % frameInterval == 0) {
        animation.addFrame(png_);
      }
    }
    animation.addFrame(png_);
  }
  return animation;
}
