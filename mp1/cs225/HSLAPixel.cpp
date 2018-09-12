/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 */

#include "HSLAPixel.h"

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  HSLAPixel::HSLAPixel() {
    h = 0.0;
    s = 0.0;
    l = 1.0;
    a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminosity) {
    h = hue;
    s = saturation;
    l = luminosity;
    a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminosity, double alpha) {
    h = hue;
    s = saturation;
    l = luminosity;
    a = alpha;
  }
}
