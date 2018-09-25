#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image fridge; fridge.readFromFile("fridge.png");
  Image s1; s1.readFromFile("logo1.png");
  Image s2; s2.readFromFile("logo2.png");
  Image s3; s3.readFromFile("logo3.png");
  
  StickerSheet sheet = StickerSheet(fridge, 3);
  sheet.addSticker(s1, 450, 150);
  sheet.addSticker(s2, 475, 700);
  sheet.addSticker(s3, 550, 400);

  sheet.render().writeToFile("myImage.png");

  return 0;
}
