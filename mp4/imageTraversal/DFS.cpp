#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS

 std::vector<Point> alreadyVisited;
 std::stack<Point> toVisit;
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
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
        points.push_back(start);
        alreadyVisited[start.x][start.y] = true;
        currentVisited[start.x][start.y] = true;
        op = png.getPixel(start.x, start.y);
    }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
    /** @todo [Part 1] */
    if (point.x < tImage.width() && point.y < tImage.height()) {
        if (!alreadyVisited[point.x][point.y]) {

            HSLAPixel & temp = tImage.getPixel(point.x, point.y);
            if (ImageTraversal::calculateDeltaHelper(temp, op) <= tol) {
                points.push_back(point);
                alreadyVisited[point.x][point.y] = true;
                currentVisited[point.x][point.y] = true;
            }
        } else {
            if (currentVisited[point.x][point.y]) {
                points.erase(std::find(points.begin(), points.end(), point));
                points.push_back(point);
            }
            /*
            if (std::find(points.begin(), points.end(), point) != points.end()) {
            points.erase(std::find(points.begin(), points.end(), point));
            points.push_back(point);
            }*/
        }
    }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
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
Point DFS::peek() const {
  /** @todo [Part 1] */
  if (points.empty()) return Point(-1, -1);
  return points.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return points.empty();
}
