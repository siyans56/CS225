#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("alma.png");
  Image i;
  i.readFromFile("i.png");

  StickerSheet sheet(alma, 3);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 300, 200);
  sheet.addSticker(i, 150, 200);

  Image final = sheet.render();
  final.writeToFile("myImage.png");
  
  return 0;
}
