/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
using namespace std;

class StickerSheet {
public:
  string test;
  unsigned arrmax;
  Image* imgar;
  unsigned* xarr;
  unsigned* yarr;
  Image blank;
  StickerSheet(const Image & picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet & other);

  const StickerSheet & operator=(const StickerSheet & other); //rule of three?
  void changeMaxStickers(unsigned max);
  int addSticker(Image & sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image * getSticker(unsigned indiex) const;
  Image render() const;
private:
};
