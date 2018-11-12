/* Your code here! */
#include "dsets.h"

/*
 * Creates n unconnected root nodes at the end of the vector.
 *
 * @param num - The number of nodes to create.
*/
void DisjointSets::addelements(int num) {
    // Add num elements each in their own disjoint set.
	for (int i = 0; i < num; i++)
		elems.push_back(-1);
}

/*
 * This function should compress paths and works as described in lecture.
 *
 * @param elem - The element (index) to find.
 * @return - The index of the root of the up-tree in which the parameter element
 * resides.
*/
int DisjointSets::find(int elem) {
    // Check if elem is a root.
	if (elems[elem] < 0)
		return elem;

    // Remove depth of the path and return the root.
	elems[elem] = find(elems[elem]);
	return elems[elem];
}

/*
 * Union by size of two sets. Root of the larger set stays as the root.
 *
 * @param a - Index of the first element to union.
 * @param b - Index of the second element to union.
*/
void DisjointSets::setunion(int a, int b) {
	int rootOfA = find(a);
	int rootOfB = find(b);

    // Check if they are part of the same set.
	if (rootOfA == rootOfB) return;

    // Merge the size of the sets. Will be negative.
	int newSize = elems[rootOfA] + elems[rootOfB];

    // Merge the smaller set into the bigger set. If equal, b's set will be
    // merged into a's set.
	if (elems[rootOfA] <= elems[rootOfB]) {
		elems[rootOfB] = rootOfA;
		elems[rootOfA] = newSize;
	} else {
		elems[rootOfA] = rootOfB;
		elems[rootOfB] = newSize;
    }
}

/*
 * Size of the set this element resides in.
 *
 * @param elem - The element (index) to check.
 * @return - Size of the set.
*/
int DisjointSets::size(int elem) {
    // Check if the element is a valid index.
    if (elem < 0 || elem >= (int) elems.size())
        return 0;

    // Return the size stored in the root node. (Value is originally negative)
    return -1 * elems[find(elem)];
}
