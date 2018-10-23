
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG bgImage = PNG();
  bgImage.readFromFile("terminal.png");
  FloodFilledImage ff = FloodFilledImage(bgImage);
  Point sp = Point(1,1);
  DFS search1 = DFS(bgImage, sp, 0.6);
  MyColorPicker cp = MyColorPicker();
  ff.addFloodFill(search1, cp);
  DFS search2 = DFS(bgImage, sp, 0.6);
  RainbowColorPicker cp2 = RainbowColorPicker(10);
  Animation animation = ff.animate(300);
  ff.addFloodFill(search2, cp2);
  //bgImage = lastFrame;
  Animation animation2 = ff.animate(300);
  for (unsigned i = 0; i < animation2.frameCount(); i++) {
      animation.addFrame(animation2.getFrame(i));
  }
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
