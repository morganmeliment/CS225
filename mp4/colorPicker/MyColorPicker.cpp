#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
    /* @todo [Part 3] */
    int bounds = (x * y) / 15;
    if (bounds > 360) {
        bounds = 360;
    }

    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> unif(0, bounds);
    //std::default_random_engine engine;
    double randVal = unif(rng);
    //double randVal1 = unif(engine);

    return HSLAPixel(
        randVal,
        1.0,
        0.5
    );
}
