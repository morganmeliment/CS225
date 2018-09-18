#include "Image.h"
#include "cs225/PNG.h"
using cs225::PNG;
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

void Image::lighten() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l += 0.1;

            if (pixel.l > 1) {
                pixel.l = 1;
            } else if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l += amount;

            if (pixel.l > 1) {
                pixel.l = 1;
            } else if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l -= 0.1;

            if (pixel.l > 1) {
                pixel.l = 1;
            } else if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l -= amount;

            if (pixel.l > 1) {
                pixel.l = 1;
            } else if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s += 0.1;

            if (pixel.s > 1) {
                pixel.s = 1;
            } else if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s += amount;

            if (pixel.s > 1) {
                pixel.s = 1;
            } else if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s -= 0.1;

            if (pixel.s > 1) {
                pixel.s = 1;
            } else if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s -= amount;

            if (pixel.s > 1) {
                pixel.s = 1;
            } else if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.h += degrees;

            while (pixel.h > 360) {
                pixel.h -= 360.0;
            }
            while (pixel.h < 0) {
                pixel.h += 360.0;
            }
        }
    }
}

double getColorDistance(double h1, double h2) {
  double max = h1;
  double min = h2;

  if (h2 > max) {
    max = h2;
    min = h1;
  }

  double d1 = max - min;
  double d2 = 360.0 - max + min;

  if (d1 <= d2) {
    return d1;
  }
  return d2;
}

void Image::illinify() {
    for (unsigned i = 0; i < height(); i++) {
        for (unsigned j = 0; j < width(); j++) {
            HSLAPixel & pixel = getPixel(j, i);

            double d1 = getColorDistance(pixel.h, 11.0);
            double d2 = getColorDistance(pixel.h, 216.0);

            if (d1 <= d2) {
                pixel.h = 11.0;
            } else {
                pixel.h = 216.0;
            }
        }
    }
}

void Image::scale(double factor) {
    if (factor < 0)
        return;

    PNG * tempPNG = new PNG(width(), height());

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            HSLAPixel & pixel2 = tempPNG->getPixel(x, y);

            pixel2.h = pixel.h;
            pixel2.s = pixel.s;
            pixel2.l = pixel.l;
            pixel2.a = pixel.a;
        }
    }

    resize((int) (width() * factor), (int) (height() * factor));

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            HSLAPixel & pixel2 = tempPNG->getPixel((int) (x / factor), (int) (y / factor));

            pixel.h = pixel2.h;
            pixel.s = pixel2.s;
            pixel.l = pixel2.l;
            pixel.a = pixel2.a;
        }
    }

    delete tempPNG;
    tempPNG = NULL;
}

void Image::scale(unsigned w, unsigned h) {
    PNG * tempPNG = new PNG(width(), height());

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            HSLAPixel & pixel2 = tempPNG->getPixel(x, y);

            pixel2.h = pixel.h;
            pixel2.s = pixel.s;
            pixel2.l = pixel.l;
            pixel2.a = pixel.a;
        }
    }

    double wFactor = ((double) w) / ((double) width());
    double hFactor = ((double) h) / ((double) height());

    resize(w, h);

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            HSLAPixel & pixel2 = tempPNG->getPixel((int) (x / wFactor), (int) (y / hFactor));

            pixel.h = pixel2.h;
            pixel.s = pixel2.s;
            pixel.l = pixel2.l;
            pixel.a = pixel2.a;
        }
    }

    delete tempPNG;
    tempPNG = NULL;
}
