/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <vector>
#include <map>

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        StickerSheet const & operator= (const StickerSheet &other);

        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index) const;
        Image render() const;

    private:
        const Image &backgroundImage;
        Image* images;
        std::map<Image*, std::vector<int>> coordinateMap;



};
