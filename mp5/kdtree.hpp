/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if (curDim >= Dim) return true;
    if (first[curDim] < second[curDim]) return true;
    if (first[curDim] > second[curDim]) return false;

    return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double currentDistance = 0;
    double potentialDistance = 0;
    for (int i = 0; i < Dim; i++) {
        currentDistance += pow(target[i] - currentBest[i], 2);
        potentialDistance += pow(target[i] - potential[i], 2);
    }

    if (potentialDistance == currentDistance) return potential < currentBest;
    if (potentialDistance < currentDistance) return true;
    return false;
}

template <int Dim>
void KDTree<Dim>::swapPoints(vector<Point<Dim>>& points, int ind1, int ind2) {
    if (ind1 >= (int) points.size() || ind1 < 0
        || ind2 >= (int) points.size() || ind2 < 0)
        return;

    Point<Dim> temp = points.at(ind1);
    points.at(ind1) = points.at(ind2);
    points.at(ind2) = temp;
}

template <int Dim>
int KDTree<Dim>::partitionQS(vector<Point<Dim>>& points, int leftInd,
                            int rightInd, int pivotIndex, int d) {
    Point<Dim> pivotValue = points.at(pivotIndex);
    swapPoints(points, pivotIndex, rightInd);
    int storedIndex = leftInd;

    for (int i = leftInd; i < rightInd; i++) {
        if (smallerDimVal(points.at(i), pivotValue, d)) {
            swapPoints(points, storedIndex, i);
            storedIndex++;
        }
    }

    swapPoints(points, storedIndex, rightInd);
    return storedIndex;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::quickSelectBuildTree(vector<Point<Dim>>& points, int leftInd,
                                int rightInd, int k, int d) {
    if (points.empty() || leftInd > rightInd)
        return NULL;
    if (leftInd == rightInd)
        return new KDTreeNode(points.at(leftInd));

    int pivotIndex = ((rightInd - leftInd) / 2) + leftInd;
    pivotIndex = partitionQS(points, leftInd, rightInd, pivotIndex, d);

    if (k == pivotIndex)
        return new KDTreeNode(points.at(k));
    else if (k < pivotIndex)
        return quickSelectBuildTree(points, leftInd, pivotIndex - 1, k, d);
    else
        return quickSelectBuildTree(points, pivotIndex + 1, rightInd, k, d);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int leftInd,
                                int rightInd, int d) {
    if (points.empty() || leftInd > rightInd)
        return NULL;
    if (leftInd == rightInd)
        return new KDTreeNode(points.at(leftInd));

    int pivotIndex = ((rightInd - leftInd) / 2) + leftInd;
    KDTreeNode * parentNode = quickSelectBuildTree(points, leftInd, rightInd,
                                                                pivotIndex, d);
    parentNode->left = buildTree(points, leftInd, pivotIndex - 1, (d + 1) % Dim);
    parentNode->right = buildTree(points, pivotIndex + 1, rightInd, (d + 1) % Dim);

    return parentNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> tempPoints = newPoints;
    size = tempPoints.size();
    root = NULL;
    if (!tempPoints.empty()) {
        root = buildTree(tempPoints, 0, tempPoints.size() - 1, 0);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = other->root;
  size = other->size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return KDTree<Dim>(rhs);
}

template <int Dim>
KDTree<Dim>::~KDTree() {
    delete root;
}

template <int Dim>
Point<Dim> KDTree<Dim>::nearestNeighborHelper(const Point<Dim>& query, KDTreeNode * curr, int dimension) const {
    if (!curr->left && !curr->right)
        return curr->point;
    Point<Dim> currentBest = curr->point;
    if (smallerDimVal(query, curr->point, dimension)) {
        if (curr->left) {
            Point<Dim> tempBest = nearestNeighborHelper(query, curr->left, (dimension + 1) % Dim);
            if (shouldReplace(query, currentBest, tempBest)) {
                currentBest = tempBest;
            }
        }
        if (curr->right) {
            Point<Dim> idealPoint = query;
            idealPoint[dimension] = curr->point[dimension];
            if (shouldReplace(query, currentBest, idealPoint)) {
                Point<Dim> tempBest = nearestNeighborHelper(query, curr->right, (dimension + 1) % Dim);
                if (shouldReplace(query, currentBest, tempBest))
                    currentBest = tempBest;
            }
        }
    } else {
        if (curr->right) {
            Point<Dim> tempBest = nearestNeighborHelper(query, curr->right, (dimension + 1) % Dim);
            if (shouldReplace(query, currentBest, tempBest))
                currentBest = tempBest;
        }
        if (curr->left) {
            Point<Dim> idealPoint = query;
            idealPoint[dimension] = curr->point[dimension];
            if (shouldReplace(query, currentBest, idealPoint)) {
                Point<Dim> tempBest = nearestNeighborHelper(query, curr->left, (dimension + 1) % Dim);
                if (shouldReplace(query, currentBest, tempBest))
                    currentBest = tempBest;
            }
        }
    }


    return currentBest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return nearestNeighborHelper(query, root, 0);
}
