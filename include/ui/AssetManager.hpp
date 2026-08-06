//
// Created by timothy on 7/30/26.
//

#ifndef FNAFONDS_ASSETMANAGER_HPP
#define FNAFONDS_ASSETMANAGER_HPP

#include <array>
#include <cstdlib>
#include <nds.h>
#include <vector>
#include <memory>
#include "shared/load.h"

constexpr int numOfBackgrounds = 40;
constexpr int numOfSprites = 20;
constexpr int spritesOAMSize = 16;

namespace ui {
    /**
     * @class Background
     * @author MattMark
     *
     * Contains background graphics data in RAM
     */
    class Background {
        std::unique_ptr<u8[]> gfx;  ///< Contains tile data
        u16 gfxLen = 0;             ///< The size of the tile data
        std::unique_ptr<u8[]> map;  ///< Contains tile map data
        u16 mapLen = 0;             ///< The size of the tile map data
        std::unique_ptr<u8[]> pal;  ///< Contains palette data
        u16 palLen = 0;             ///< The size of the palette data

    public:
        Background() = default;
        Background(const unsigned int newGfx[], unsigned int newGfxLen,
                    const short unsigned int newMap[], unsigned int newMapLen,
                    const short unsigned int newPal[], unsigned int newPalLen);
        [[nodiscard]] u8* getGfx() const { return gfx.get(); }
        [[nodiscard]] unsigned int getGfxLen() const { return gfxLen; }
        [[nodiscard]] u8* getMap() const { return map.get(); }
        [[nodiscard]] unsigned int getMapLen() const { return mapLen; }
        [[nodiscard]] u8* getPal() const { return pal.get(); }
        [[nodiscard]] unsigned int getPalLen() const { return palLen; }

    };

    /**
     * @class Sprite
     * @author MattMark
     *
     * Contains sprite graphics data in RAM
     */
    class Sprite {
        std::unique_ptr<u8[]> gfx;  ///< Contains sprite data
        u16 gfxLen = 0;             ///< The size of the sprite data
        std::unique_ptr<u8[]> pal;  ///< Contains palette data
        u16 palLen = 0;             ///< The size of the palette data

    public:
        Sprite() = default;
        Sprite(const unsigned int newGfx[], unsigned int gfxLen,
                    const short unsigned int newPal[], unsigned int palLen);

        [[nodiscard]] u8* getGfx() const { return gfx.get(); }
        [[nodiscard]] unsigned int getGfxLen() const { return gfxLen; }
        [[nodiscard]] u8* getPal() const { return pal.get(); }
        [[nodiscard]] unsigned int getPalLen() const { return palLen; }
    };

    /**
     * @class SpriteOAMSlot
     * @author MattMark
     *
     * Contains information about a sprite in OAM
     */
    class SpriteOAMSlot {
        u16* gfxPtr = nullptr;              ///< The pointer of the allocated vram
        SpriteSize size = SpriteSize_32x32; ///< The sprite size
        SpriteColorFormat colorFormat = SpriteColorFormat_16Color;  ///< The color format

    public:
        SpriteOAMSlot(u16* newGfxPtr, SpriteSize newSize, SpriteColorFormat colorFormat);
        SpriteOAMSlot() = default;

        [[nodiscard]] u16* getGfxPtr() const { return gfxPtr; }
        void setGfxPtr(u16* newGfxPtr) { gfxPtr = newGfxPtr; }
        [[nodiscard]] SpriteSize getSize() const { return size; }
        [[nodiscard]] SpriteColorFormat getColorFormat() const { return colorFormat; }

    };

    /**
     * @class AssetManager
     * @author MattMark
     *
     * High-level interface for loading and rendering backgrounds and sprites
     */
    class AssetManager {
        int bgs[2] = {0, 0};

        std::array<Background, numOfBackgrounds> backgrounds;   ///< Contains all Background data
        std::array<Sprite, numOfSprites> sprites;               ///< Contains all Sprite data
        std::array<SpriteOAMSlot, spritesOAMSize> spritesOAM;   ///< Contains all Sprite OAM data
        std::array<SpriteOAMSlot, spritesOAMSize> spritesOAMSub;///< Contains all Sprite OAM data for sub screen

    public:
        AssetManager();
        ~AssetManager();

        /**
         * Displays a loading sprite
         */
        void showLoadSprite();

        /**
         * Hides the loading sprite
         */
        void hideLoadSprite();

        //
        // Background
        //

        /**
         * Load a background into RAM
         * @param index The index in the backgrounds array to store the background
         * @param newGfx A pointer for the tile graphics
         * @param gfxLen size of the tile graphics in bytes
         * @param newMap A pointer for the tile map
         * @param mapLen size of the tile graphics in bytes
         * @param newPal A pointer for the palette
         * @param palLen size of the tile graphics in bytes
         */
        void loadBackground(u8 index, const unsigned int newGfx[], unsigned int gfxLen,
                    const short unsigned int newMap[], unsigned int mapLen,
                    const short unsigned int newPal[], unsigned int palLen);

        /**
         * Get a Background from RAM
         * @param index The index in the backgrounds array to retrieve
         * @return A reference to a Background
         */
        Background& getBackground(u8 index);

        /**
         * load background into VRAM and display it
         * @param index The index in the backgrounds array
         * @param layer The background layer to display it
         */
        void showBackground(u8 index, u8 layer);

        //
        // Sprite
        //

        /**
         * Load a sprite into RAM
         * @param index The index in the sprites array to store the sprite
         * @param newGfx A pointer for the sprite graphics
         * @param gfxLen size of the tile graphics in bytes
         * @param newPal A pointer for the palette
         * @param palLen size of the tile graphics in bytes
         */
        void loadSpriteRAM(u8 index, const unsigned int newGfx[], unsigned int gfxLen,
                    const short unsigned int newPal[], unsigned int palLen);

        /**
         * Get a Sprite from RAM
         * @param index The index in the sprites vector to retrieve
         * @return A reference to a Sprite
         */
        Sprite& getSprite(u8 index);

        /**
         * Load a sprite into OAM (VRAM)
         * @param ramIndex The index in the sprites array to load
         * @param oamIndex The index in the sprites vram array to load it in
         * @param size The size of the sprite
         * @param colorFormat The color format of the sprite
         * @param subScreen The screen the sprite should be loaded on
         */
        void loadSpriteVRAM(u8 ramIndex, u8 oamIndex, SpriteSize size, SpriteColorFormat colorFormat, bool subScreen);

        /**
         * Remove a sprite loaded in OAM
         * @param oamIndex The index in the sprites vram array to unload
         * @param subScreen The screen the sprite should be unloaded from
         */
        void unloadSpriteVRAM(u8 oamIndex, bool subScreen);

        /**
         * Remove all sprites loaded in OAM
         * @param subScreen The screen the sprites should be unloaded from
         */
        void unloadSpriteVRAMAll(bool subScreen);

        /**
         * Replace the graphics data of a sprite in OAM
         * @param ramIndex The index in the sprites array to load
         * @param oamIndex The index in the sprites vram array to load it in
         * @param subScreen The screen the sprite is loaded on
         */
        void overwriteSpriteVRAM(u8 ramIndex, u8 ramOffset, u8 oamIndex, bool subScreen);

        /**
         * Render a sprite on screen
         * @param id The id to give the sprite [0-127]
         * @param oamIndex The index in the sprites vram array to load it in
         * @param subScreen The screen the sprite should be rendered on
         * @param x The x position of the sprite
         * @param y The y position of the sprite
         * @param priority The render priority [0-3]
         */
        void addSprite(u8 id, u8 oamIndex, bool subScreen, s16 x, s16 y, u8 priority);

        /**
         * Change sprite on screen to a different sprite in OAM
         * @param id The id to give the sprite [0-127]
         * @param oamIndex The index in the sprites vram array to load it in
         * @param subScreen The screen the sprite is rendered on
         */
        void changeSprite(u8 id, u8 oamIndex, bool subScreen);

        /**
         * Move a sprite on screen
         * @param id The id to give the sprite [0-127]
         * @param subScreen The screen the sprite is rendered on
         * @param x The x position of the sprite
         * @param y The y position of the sprite
         */
        void moveSprite(u8 id, bool subScreen, s16 x, s16 y);

        /**
         * Hide a sprite on screen
         * @param id The id to give the sprite [0-127]
         * @param subScreen The screen the sprite is rendered on
         * @param hide Should the sprite be hidden
         */
        void hideSprite(u8 id, bool subScreen, bool hide);

        /**
         * Remove a sprite on screen
         * @param id The id to give the sprite [0-127]
         * @param subScreen The screen the sprite is rendered on
         */
        void removeSprite(u8 id, bool subScreen);

        /**
         * Remove all sprites on screen
         * @param subScreen The screen the sprites are on
         */
        void removeAllSprites(bool subScreen);

    };
}

#endif //FNAFONDS_ASSETMANAGER_HPP