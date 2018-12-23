
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG inpic;
  inpic.readFromFile("goku2.png");
  PNG pic2;
  pic2.readFromFile("golden_frieza_25.png");
  FloodFilledImage myimg(inpic);

  DFS dfs1(inpic, Point(33,22), .09);
  DFS dfs2(inpic, Point(4,88), .09);
  DFS dfs3(inpic, Point(10,118), .09);
  DFS dfs4(inpic, Point(20,220), .09);
  DFS dfs5(inpic, Point(92,237), .09);
  DFS dfs6(inpic, Point(108,205), .09);
  DFS dfs7(inpic, Point(172,227), .09);
  DFS dfs8(inpic, Point(182,9), .09);
  DFS dfs9(inpic, Point(113,5), .09);
  DFS dfs10(inpic, Point(69,54), .09);


  MyColorPicker blue(inpic);
  myimg.addFloodFill(dfs1, blue);
  myimg.addFloodFill(dfs2, blue);
  myimg.addFloodFill(dfs3, blue);
  myimg.addFloodFill(dfs4, blue);
  myimg.addFloodFill(dfs5, blue);
  myimg.addFloodFill(dfs6, blue);
  myimg.addFloodFill(dfs7, blue);
  myimg.addFloodFill(dfs8, blue);
  myimg.addFloodFill(dfs9, blue);
  myimg.addFloodFill(dfs10, blue);

  //BFS second(inpic, Point(488,184), .05);
  BFS second(inpic, Point(48,110), .09);
  RainbowColorPicker rcp(1);
  myimg.addFloodFill(second, rcp);

  Animation animation = myimg.animate(7500);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

/*
PNG png;      png.readFromFile("input.png");
PNG black;    black.readFromFile("golden_frieza_25.png");

FloodFilledImage image(png);
DFS dfs(png, Point(0, 0), 0.2);
MyColorPicker mine(black);
image.addFloodFill( dfs, mine );
BFS bfs(png, Point(110, 150), 0.05);
RainbowColorPicker rainbow(0.1);
image.addFloodFill( bfs, rainbow );


Animation animation = image.animate(10000);
PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
lastFrame.writeToFile("myFloodFill.png");
animation.write("myFloodFill.gif"); */

  return 0;
}
