/* Your code here! */
#include "maze.h"

bool SquareMaze::hasSeededRandom = false;

void SquareMaze::makeMaze(int width, int height) {
	if (!hasSeededRandom) {
		srand(time(NULL));
		hasSeededRandom = true;
	}

	rightWalls.clear();
	downWalls.clear();

	w = width;
	h = height;
	size = w * h;

	for (int i = 0; i < size; i++) {
		rightWalls.push_back(true);
		downWalls.push_back(true);
	}

	DisjointSets dSet;
	dSet.addelements(size);

	int edges = 0;

	while (edges < size - 1) {
		int edge = rand() % size;
		int collision = rand() % 2;

		if (collision == 0 && edge % w != w - 1) {
			if (dSet.find(edge) != dSet.find(edge + 1)) {
				setWall(edge % w, edge / h, 0, false);
				dSet.setunion(edge, edge + 1);
				edges++;
			}
		} else if (collision == 1 && edge / h != h - 1) {
			if (dSet.find(edge) != dSet.find(edge + w)) {
				setWall(edge % w, edge / h, 1, false);
				dSet.setunion(edge, edge + w);
				edges++;
			}
		}
	}
}

void SquareMaze::makeMazeCreative(int width, int height) {
	if (!hasSeededRandom) {
		srand(time(NULL));
		hasSeededRandom = true;
	}

	rightWalls.clear();
	downWalls.clear();

	w = width;
	h = height;
	size = w * h;
	int radius = w / 2;
	if (radius > h / 2) radius = h / 2;

	for (int i = 0; i < size; i++) {
		rightWalls.push_back(true);
		downWalls.push_back(true);
	}

	DisjointSets dSet;
	dSet.addelements(size);

	int edges = 0;

	while (edges < pow(radius, 2) * 3.14159) {
		int edge = rand() % size;
		int collision = rand() % 2;

		if (collision == 0 && edge % w != w - 1 && sqrt(pow(edge % w - w / 2, 2) + pow(edge / h - h / 2, 2)) < radius) {
			if (dSet.find(edge) != dSet.find(edge + 1)) {
				setWall(edge % w, edge / h, 0, false);
				dSet.setunion(edge, edge + 1);
				edges++;
			}
		} else if (collision == 1 && edge / h != h - 1 && sqrt(pow(edge % w - w / 2, 2) + pow(edge / h - h / 2, 2)) < radius) {
			if (dSet.find(edge) != dSet.find(edge + w)) {
				setWall(edge % w, edge / h, 1, false);
				dSet.setunion(edge, edge + w);
				edges++;
			}
		}
	}

	for (int i = 0; i <= h / 2; i++) {
		setWall(0, i, 0, false);
		setWall(0, i, 1, false);
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
	if (dir == 0) {
		if (x == w - 1)
			return false;

		return !rightWalls[y * w + x];
	} else if (dir == 1) {
		if (y == h - 1)
			return false;

		return !downWalls[y * w + x];
	} else if (dir == 2) {
		if (x == 0)
			return false;

		return !rightWalls[y * w + x - 1];
	} else if (dir == 3) {
		if (y == 0)
			return false;

		return !downWalls[(y - 1) * w + x];
	}

	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
	if (dir == 0)
		rightWalls[y * w + x] = exists;
	else if (dir == 1)
		downWalls[y * w + x] = exists;
}

vector<int> SquareMaze::solveMaze() {
	vector<vector<int>> mazeData(size, vector<int>(3, -1));
	queue<int> cellVisitQueue;
	cellVisitQueue.push(0);

	while (!cellVisitQueue.empty()) {
		int cell = cellVisitQueue.front();
		cellVisitQueue.pop();

		int x = cell % w;
		int y = (cell - x) / w;

		if (canTravel(x, y, 0)) {
			if (mazeData[cell + 1][0] < 0) {
				vector<int> temp {
					mazeData[cell][0] + 1,
					0,
					cell
				};

				mazeData[cell + 1] = temp;
				cellVisitQueue.push(cell + 1);
			}
		}
		if (canTravel(x, y, 1)) {
			if (mazeData[cell + w][0] < 0) {
				vector<int> temp {
					mazeData[cell][0] + 1,
					1,
					cell
				};

				mazeData[cell + w] = temp;
				cellVisitQueue.push(cell + w);
			}
		}
		if (canTravel(x, y, 2)) {
			if (mazeData[cell - 1][0] < 0) {
				vector<int> temp {
					mazeData[cell][0] + 1,
					2,
					cell
				};

				mazeData[cell - 1] = temp;
				cellVisitQueue.push(cell - 1);
			}
		}
		if (canTravel(x, y, 3)) {
			if (mazeData[cell - w][0] < 0) {
				vector<int> temp {
					mazeData[cell][0] + 1,
					3,
					cell
				};

				mazeData[cell - w] = temp;
				cellVisitQueue.push(cell - w);
			}
		}
	}

	int destinationCell = w * (h - 1);
	for (int i = destinationCell + 1; i < size; i++)
		if (mazeData[i][0] > mazeData[destinationCell][0])
			destinationCell = i;

	int tempCell = destinationCell;
	vector<int> finalPath;
	while (tempCell > 0) {
		finalPath.push_back(mazeData[tempCell][1]);
		tempCell = mazeData[tempCell][2];
	}

	reverse(finalPath.begin(), finalPath.end());

	return finalPath;
}


PNG * SquareMaze::drawMaze() const {
	PNG * mazeImage = new PNG(w * 10 + 1, h * 10 + 1);
	HSLAPixel black = HSLAPixel(0.0, 0.0, 0.0);

	for (int i = 10; i <= w * 10; i++)
		mazeImage->getPixel(i, 0) = black;
	for (int i = 0; i <= h * 10; i++)
		mazeImage->getPixel(0, i) = black;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (!canTravel(i, j, 0)) {
				for (int q = 0; q<= 10; q++) {
					mazeImage->getPixel((i + 1) * 10, j * 10 + q) = black;
				}
			}

			if (!canTravel(i, j, 1)) {
				for (int q = 0; q <= 10; q++) {
					mazeImage->getPixel(i * 10 + q, (j + 1) * 10) = black;
				}
			}
		}
	}

	return mazeImage;
}

PNG * SquareMaze::drawMazeWithSolution() {
	PNG * mazeImage = drawMaze();
	vector<int> finalPath = solveMaze();

	int x = 5;
	int y = 5;

	HSLAPixel red = HSLAPixel(360.0, 1.0, 0.5);
	HSLAPixel white = HSLAPixel(360.0, 1.0, 1.0);

	for (int i = 0; i < (int) finalPath.size(); i++) {
		if (finalPath[i] == 0) {
			for (int j = 0; j <= 10; j++) {
				mazeImage->getPixel(x + j, y) = red;
			}

			x += 10;
		}
		if (finalPath[i] == 1) {
			for (int j = 0; j <= 10; j++) {
				mazeImage->getPixel(x, y + j) = red;
			}

			y += 10;
		}
		if (finalPath[i] == 2) {
			for (int j = 0; j <= 10; j++) {
				mazeImage->getPixel(x - j, y) = red;
			}

			x -= 10;
		}
		if (finalPath[i] == 3) {
			for (int j = 0; j <= 10; j++) {
				mazeImage->getPixel(x, y - j) = red;
			}

			y -= 10;
		}
	}

	x -= 5;
	y += 5;

	for (int j = 1; j < 10; j++)
		mazeImage->getPixel(x + j, y) = white;

	return mazeImage;
}


PNG * SquareMaze::drawCreativeMaze() {
	PNG * mazeImage = drawMaze();
	PNG * mazeImageFinal = new PNG(*mazeImage);
	vector<int> finalPath = solveMaze();

	int x = 5;
	int y = 5;

	HSLAPixel red = HSLAPixel(360.0, 1.0, 0.5);
	HSLAPixel white = HSLAPixel(360.0, 1.0, 1.0);
	HSLAPixel black = HSLAPixel(0.0, 0.0, 0.0);

	for (int i = 0; i < (int) finalPath.size(); i++) {
		if (finalPath[i] == 0) {
			for (int j = 0; j <= 10; j++) {
				mazeImage->getPixel(x + j, y) = red;
			}

			x += 10;
		}
		if (finalPath[i] == 1) {
			for (int j = 0; j <= 10; j++) {
				mazeImage->getPixel(x, y + j) = red;
			}

			y += 10;
		}
		if (finalPath[i] == 2) {
			for (int j = 0; j <= 10; j++) {
				mazeImage->getPixel(x - j, y) = red;
			}

			x -= 10;
		}
		if (finalPath[i] == 3) {
			for (int j = 0; j <= 10; j++) {
				mazeImage->getPixel(x, y - j) = red;
			}

			y -= 10;
		}
	}

	x -= 5;
	y += 5;

	for (int j = 1; j < 10; j++)
		mazeImage->getPixel(x + j, y) = white;

	double centerX = w * 5;
	double centerY = h * 5;
	double radius = centerX;
	if (radius > centerY) radius = centerY;

	for (int x = 0; x <= w * 10; x++) {
		for (int y = 0; y <= h * 10; y++) {
			double d = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
			double m = pow(d / (radius), 2);
			//if (dist > radius)
				//mazeImage->getPixel(x, y) = white;
			if (d > radius) {
				mazeImage->getPixel(x, y) = black;
				mazeImageFinal->getPixel(x, y) = black;
			} else {
				mazeImageFinal->getPixel(x, y) = mazeImage->getPixel(m * (x - centerX) + centerX, m * (y - centerY) + centerY);
			}

		}
	}

	delete mazeImage;

	return mazeImageFinal;
}
