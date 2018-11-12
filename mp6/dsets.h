/* Your code here! */

#ifndef DSETS_H
#define DSETS_H

#include <vector>

class DisjointSets {
	public:
        /*
         * Creates n unconnected root nodes at the end of the vector.
         *
         * @param num - The number of nodes to create.
        */
    	void addelements(int num);

        /*
         * This function should compress paths and works as described in lecture.
         *
         * @param elem - The element (index) to find.
         * @return - The index of the root of the up-tree in which the parameter element
         * resides.
        */
    	int find(int elem);

        /*
         * Union by size of two sets. Root of the larger set stays as the root.
         *
         * @param a - Index of the first element to union.
         * @param b - Index of the second element to union.
        */
    	void setunion(int a, int b);

        /*
         * Size of the set this element resides in.
         *
         * @param elem - The element (index) to check.
         * @return - Size of the set.
        */
        int size(int elem);
	private:
        // The vector elements for our disjoint sets.
        std::vector<int> elems;
};

#endif
