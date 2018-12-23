/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
 MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
 std::vector<Point<3>> vectorTree;
 std::map<Point<3>, int> mapTiles;

 for (unsigned a = 0; a < theTiles.size(); a++) {
   //we are filling up the vector,
   Point<3> p = convertToXYZ(theTiles[a].getAverageColor());
   vectorTree.push_back(p);
 }

 KDTree<3> conTree(vectorTree);
 for (unsigned b = 0; b < vectorTree.size(); b++) {
   //now filling up the map, with index
   mapTiles.insert( pair<Point<3>,int> (vectorTree[b], b));
 }

 std::vector<TileImage> & tiles = theTiles;


 for (int i = 0; i < canvas->getRows(); i++) {
   for (int j = 0; j < canvas->getColumns(); j++) {
     // set a pixel from the source to and xyz pixel
     Point<3> xyzPix = convertToXYZ(theSource.getRegionColor(i,j));
     //set a tile in the canvas to an image created by findNearestNeighbor
     canvas->setTile(i, j, switchUp(conTree, xyzPix, mapTiles, theTiles));
   }
 }
return canvas;


}
//the constant variables need to stay constant, and require a reference to each variable
//therefore we must ahve a sepearate method to find the nearest findNearestNeighbor
//using the map, kdtree, and extra variables in order to do so.
TileImage* switchUp(const KDTree<3>& switchTree, Point<3> converted,
   map<Point<3>, int> map,vector<TileImage>& tiles ) {
     //finds the nearest neighbor to the xyz pix in the kdtree
  Point<3> nPix = switchTree.findNearestNeighbor(converted);
  //returns the tileimage based on the index based on the pixel in the map found.
  return &tiles[map[nPix]];
}
