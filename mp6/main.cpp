#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;

    SquareMaze creativeMaze = SquareMaze();
    creativeMaze.makeMazeCreative(25, 25);
    PNG * creativeImage = creativeMaze.drawCreativeMaze();
    creativeImage->writeToFile("creative.png");
    delete creativeImage;
    return 0;
}
