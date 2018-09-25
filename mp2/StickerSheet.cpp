#include "StickerSheet.h"
#include "Image.h"
#include <vector>
#include <map>

StickerSheet::StickerSheet(const Image &picture, unsigned max) : backgroundImage(picture) {
    images = new Image[max];
    maxImages = max;
    imageCount = 0;
}

StickerSheet::~StickerSheet() {
    delete[] images;
    images = NULL;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    images = NULL;
    delete[] images;
    images = new Image[other.maxImages];
    maxImages = other.maxImages;
    imageCount = other.imageCount;
    backgroundImage = other.backgroundImage;

    std::map<Image*, std::vector<int>>::const_iterator it;
    for (int i = 0; i < imageCount && i < maxImages; i++) {
        images[i] = other.images[i];

        it = other.coordinateMap.find(&(other.images[i]));
        if (it != other.coordinateMap.end()) {
            coordinateMap.insert(std::pair<Image*,
                std::vector<int>>(&images[i], other.coordinateMap.at(&(other.images[i]))));
        }
    }
}

StickerSheet const & StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        delete[] images;
        images = new Image[other.maxImages];
        maxImages = other.maxImages;
        imageCount = other.imageCount;
        backgroundImage = other.backgroundImage;

        std::map<Image*, std::vector<int>>::const_iterator it;
        for (int i = 0; i < imageCount && i < maxImages; i++) {
            images[i] = other.images[i];

            it = other.coordinateMap.find(&(other.images[i]));
            if (it != other.coordinateMap.end()) {
                coordinateMap.insert(std::pair<Image*,
                    std::vector<int>>(&images[i], other.coordinateMap.at(&(other.images[i]))));
            }
        }
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    Image* tempImages = new Image[max];
    //images = new Image[max];

    for (int i = 0; i < imageCount && i < maxImages && i < (int) max; i++) {
        tempImages[i] = images[i];
        coordinateMap.insert(std::pair<Image*,
            std::vector<int>>(&tempImages[i], coordinateMap.at(&images[i])));
        coordinateMap.erase(&images[i]);
    }

    if (imageCount > (int) max) {
        imageCount = (int) max;
    }

    maxImages = max;
    delete[] images;
    images = tempImages;
    tempImages = NULL;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (imageCount >= maxImages) {
        return -1;
    }

    images[imageCount] = sticker;

    std::vector<int> locationVector;
    locationVector.push_back(x);
    locationVector.push_back(y);
    coordinateMap.insert(std::pair<Image*,
        std::vector<int>>(&images[imageCount], locationVector));

    imageCount++;

    return imageCount - 1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if ((int) index >= imageCount) {
        return false;
    }

    Image * imageAddress = &images[index];
    std::vector<int> & currentLocationVector = coordinateMap.at(imageAddress);
    currentLocationVector.at(0) = x;
    currentLocationVector.at(1) = y;

    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if ((int) index >= imageCount) {
        return;
    }

    int offset = 0;
    std::map<Image*, std::vector<int>>::iterator it, it2;
    for (int i = 0; (i + offset) < imageCount && (i + offset) < maxImages; i++) {
        if (i == (int) index) {
            offset++;

            if (!((i + offset) < imageCount && (i + offset) < maxImages)) {
                break;
            }
        }

        if (offset != 0) {
            it = coordinateMap.find(&images[i]);
            if (it != coordinateMap.end()) {
                coordinateMap.erase(&images[i]);
                it2 = coordinateMap.find(&images[i + offset]);
                if (it2 != coordinateMap.end()) {
                    images[i] = images[i + offset];
                    coordinateMap.insert(std::pair<Image*,
                        std::vector<int>>(&images[i], coordinateMap.at(&images[i + offset])));
                } else {
                    images[i] = Image();
                    break;
                }
            } else {
                break;
            }
        }
    }
    images[maxImages - 1] = Image();

    imageCount--;
}

Image * StickerSheet::getSticker(unsigned index) const {
    if ((int) index >= (int) imageCount) {
        return nullptr;
    }

    return &images[index];
}

Image StickerSheet::render() const {
    // Calculate bounds of image.
    int maxX = backgroundImage.width();
    int maxY = backgroundImage.height();

    for (int i = 0; i < imageCount; i++) {
        int imageXLimit = coordinateMap.at(&images[i]).at(0) + images[i].width();
        int imageYLimit = coordinateMap.at(&images[i]).at(1) + images[i].height();

        if (imageXLimit > maxX) {
            maxX = imageXLimit;
        }
        if (imageYLimit > maxY) {
            maxY = imageYLimit;
        }
    }

    Image out = Image(maxX, maxY);

    for (unsigned x = 0; x < backgroundImage.width(); x++) {
        for (unsigned y = 0; y < backgroundImage.height(); y++) {
            out.getPixel(x, y) = backgroundImage.getPixel(x, y);
        }
    }

    for (int i = 0; i < imageCount; i++) {
        for (unsigned x = 0; x < images[i].width(); x++) {
            for (unsigned y = 0; y < images[i].height(); y++) {
                if (images[i].getPixel(x, y).a != 0) {
                    out.getPixel(x + coordinateMap.at(&images[i]).at(0),
                        y + coordinateMap.at(&images[i]).at(1)) = images[i].getPixel(x, y);
                }
            }
        }
    }

    return out;
}
