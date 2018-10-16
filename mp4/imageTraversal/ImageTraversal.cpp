#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  stored = NULL;
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal * searchObject) {
    /** @todo [Part 1] */
    stored = searchObject;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    if (!stored || stored->empty()) return *this;

    Point next = stored->pop();
    Point right = Point(next.x + 1, next.y);
    Point down = Point(next.x, next.y + 1);
    Point left = Point(next.x - 1, next.y);
    Point up = Point(next.x, next.y - 1);

    stored->add(right);
    stored->add(down);
    stored->add(left);
    stored->add(up);

    //if (stored->empty()) return *(new ImageTraversal::Iterator());

    return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  if (!stored || stored->empty()) return Point(-1, -1);
  return stored->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    if (!stored || stored->empty()) {
        if (const_cast<ImageTraversal::Iterator&>(other).operator *() == Point(-1, -1)) return false;
        return true;
    }
  /** @todo [Part 1] */
  return !(stored->peek() == const_cast<ImageTraversal::Iterator&>(other).operator *());
}
