/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "dsets.h"
#include "cs225/PNG.h"

using namespace cs225;
using namespace std;

class SquareMaze {
	public:
		SquareMaze() {};

		void makeMaze(int width, int height);

		void makeMazeCreative(int width, int height);

		bool canTravel(int x, int y, int dir) const;

		void setWall(int x, int y, int dir, bool exists);

		vector<int> solveMaze();

		PNG * drawMaze() const;

		PNG * drawMazeWithSolution();

		PNG * drawCreativeMaze();
	private:
		static bool hasSeededRandom;
		int w;
		int h;
		int size;

		vector<bool> rightWalls;
		vector<bool> downWalls;
};

#endif
