#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <vector>


void rotate(std::string inputFile, std::string outputFile) {
    PNG image;
    image.readFromFile(inputFile);

    PNG imageOut = PNG(image.width(), image.height());

    for (unsigned x = 0; x < image.width(); x++) {
        for (unsigned y = 0; y < image.height(); y++) {
            HSLAPixel & prePixel = image.getPixel(image.width() - x - 1, image.height() - y - 1);
            HSLAPixel & outPixel = imageOut.getPixel(x, y);
            outPixel = prePixel;
        }
    }

    imageOut.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
    PNG png(width, height);

    HSLAPixel & ogPixel = png.getPixel(0, 0);
    ogPixel.h = 200.0;
    ogPixel.s = 0.5;
    ogPixel.l = 0.1;

    for (unsigned x = 1; x < png.width(); x++) {
        for (unsigned y = 0; y < png.height(); y++) {
            HSLAPixel & outPixel = png.getPixel(x, y);
            std::vector<int> topPixel = {0, 0};
            std::vector<int> bottomPixel = {0, 0};
            std::vector<int> rightPixel = {0, 0};
            std::vector<int> leftPixel = {0, 0};
            if (y > 0) {
                topPixel[1] -= 1;
            }
            if (y < png.height() - 1) {
                bottomPixel[1] += 1;
            }
            if (x > 0) {
                leftPixel[0] -= 1;
            }
            if (x < png.width() - 1) {
                rightPixel[0] += 1;
            }

            HSLAPixel & topPixelRef = png.getPixel(x + topPixel[0], y + topPixel[1]);
            //HSLAPixel & bottomPixelRef = png.getPixel(x + bottomPixel[0], y + bottomPixel[1]);
            //HSLAPixel & rightPixelRef = png.getPixel(x + rightPixel[0], y + rightPixel[1]);
            HSLAPixel & leftPixelRef = png.getPixel(x + leftPixel[0], y + leftPixel[1]);

            outPixel.h = (1.05 * topPixelRef.h) / 2 + (leftPixelRef.h * 1.05) / 2;
            outPixel.s = 1.0;
            outPixel.l = 0.5;
            while (outPixel.h > 360) {
                outPixel.h -= 360.0;
            }
            while (outPixel.h < 0) {
                outPixel.h += 360.0;
            }
        }
    }

    return png;
}
