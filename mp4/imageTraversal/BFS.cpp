#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  tImage = png;
  startPoint = start;
  tol = tolerance;

  for (int i = 0; i < (int) png.width(); i++) {
      std::vector<bool> row;
      for (int j = 0; j < (int) png.height(); j++) {
          row.push_back(false);
      }
      alreadyVisited.push_back(row);
      currentVisited.push_back(row);
  }

  if (start.x < png.width() && start.y < png.height()) {
      points.insert(points.begin(), start);
      alreadyVisited[start.x][start.y] = true;
      currentVisited[start.x][start.y] = true;
      op = png.getPixel(start.x, start.y);
  }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  /*
  if (std::find(alreadyVisited.begin(), alreadyVisited.end(), point) == alreadyVisited.end()) {
      if (point.x < tImage.width() && point.y < tImage.height()) {
          HSLAPixel & temp = tImage.getPixel(point.x, point.y);
          if (ImageTraversal::calculateDeltaHelper(temp, op) <= tol) {

              alreadyVisited.push_back(point);
          }
      }
  }*/
  // Not neccesary on BFS I guess. Will remove later.
  // else {
        //if (std::find(points.begin(), points.end(), point) != points.end()) {
          //points.erase(std::find(points.begin(), points.end(), point));
          //points.insert(points.begin(), point);
      //}
  //}
  if (point.x < tImage.width() && point.y < tImage.height()) {
      if (!alreadyVisited[point.x][point.y]) {

          HSLAPixel & temp = tImage.getPixel(point.x, point.y);
          if (ImageTraversal::calculateDeltaHelper(temp, op) <= tol) {
              points.insert(points.begin(), point);
              alreadyVisited[point.x][point.y] = true;
              currentVisited[point.x][point.y] = true;
          }
      }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 *///.insert(points.begin(),
Point BFS::pop() {
  /** @todo [Part 1] */
  if (points.empty()) return Point(-1, -1);
  Point temp = points.back();
  currentVisited[temp.x][temp.y] = false;
  points.pop_back();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if (points.empty()) return Point(-1, -1);
  return points.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return points.empty();
}
