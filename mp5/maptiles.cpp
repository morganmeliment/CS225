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

    MosaicCanvas * canvasPtr = new MosaicCanvas(theSource.getRows(),
                                    theSource.getColumns());

    vector<Point<3>> treeInitialization;
    map<Point<3>, TileImage*> tileMap;

	for (TileImage& tile : theTiles) {
		LUVAPixel avg = tile.getAverageColor();
		Point<3> xyzAvg = convertToXYZ(avg);

		treeInitialization.push_back(xyzAvg);
		tileMap[xyzAvg] = &tile;
	}

    KDTree<3> tree = KDTree<3>(treeInitialization);

    for (int i = 0; i < theSource.getRows(); i++) {
		for (int j = 0; j < theSource.getColumns(); j++) {
			LUVAPixel color = theSource.getRegionColor(i, j);

			Point<3> xyzColor = convertToXYZ(color);
			Point<3> nearestColor = tree.findNearestNeighbor(xyzColor);

			canvasPtr->setTile(i, j, tileMap.at(nearestColor));
		}
	}

    return canvasPtr;
}
