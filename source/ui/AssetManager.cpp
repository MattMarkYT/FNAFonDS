#include "ui/AssetManager.hpp"

using namespace ui;

AssetManager::AssetManager() {

    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
    vramSetBankF(VRAM_F_LCD);

    // BG 0: Enough for 1024 Tiles
    bgs[0] = bgInitHidden(0, BgType_Text8bpp, BgSize_T_512x256, 0, 1);
    // BG 1: Enough for 768 Tiles
    bgs[1] = bgInitHidden(1, BgType_Text8bpp, BgSize_T_512x256, 2, 5);

    oamInit(&oamMain, SpriteMapping_1D_128, false);
    oamInit(&oamSub, SpriteMapping_1D_128, false);

}

AssetManager::~AssetManager() {
    unloadSpriteVRAMAll(false);
    unloadSpriteVRAMAll(true);

    vramSetPrimaryBanks(VRAM_A_LCD, VRAM_B_LCD, VRAM_C_LCD, VRAM_D_LCD);
    vramSetBankF(VRAM_F_LCD);

    dmaFillWords(0, reinterpret_cast<void *>(0x06000000), 0x600000);
    dmaFillWords(0, reinterpret_cast<void *>(0x06890000), 0x3FFF);

}

void AssetManager::showLoadSprite() {
    loadSpriteRAM(0, loadTiles, loadTilesLen, loadPal, loadPalLen);
    loadSpriteVRAM(0, 15, SpriteSize_32x32, SpriteColorFormat_16Color, false);
    sprites[0] = {};
    addSprite(127, 15, false, 223, 159, 0);
    oamUpdate(&oamMain);
    swiWaitForVBlank();
}

void AssetManager::hideLoadSprite() {
    removeSprite(127, false);
    unloadSpriteVRAM(15, false);
    oamUpdate(&oamMain);
}

void AssetManager::loadBackground(u8 index, const unsigned int *newGfx, unsigned int gfxLen,
                                const short unsigned int *newMap, unsigned int mapLen,
                                const short unsigned int *newPal, unsigned int palLen) {
    assert(index < numOfBackgrounds);
    backgrounds[index] = Background(newGfx, gfxLen, newMap, mapLen, newPal, palLen);
}

Background& AssetManager::getBackground(u8 index) {
    assert(index < numOfBackgrounds);
    return backgrounds[index];
}

void AssetManager::showBackground(u8 index, u8 layer) {
    const Background& bg = getBackground(index);
    assert(layer <= 1);
    dmaCopy(bg.getGfx(), bgGetGfxPtr(bgs[layer]), bg.getGfxLen());
    dmaCopy(bg.getMap(), bgGetMapPtr(bgs[layer]), bg.getMapLen());

    vramSetBankF(VRAM_F_LCD);
    dmaCopy(bg.getPal(), &VRAM_F_EXT_PALETTE[layer], bg.getPalLen());
    vramSetBankF(VRAM_F_BG_EXT_PALETTE_SLOT01);
    bgExtPaletteEnable();

    bgShow(bgs[layer]);
}

void AssetManager::loadSpriteRAM(u8 index, const unsigned int newGfx[], unsigned int gfxLen,
                            const short unsigned int newPal[], unsigned int palLen) {
    sprites[index] = Sprite(newGfx, gfxLen, newPal, palLen);
}

Sprite& AssetManager::getSprite(u8 index) {
    assert(index < sprites.size());
    return sprites[index];
}

void AssetManager::loadSpriteVRAM(u8 ramIndex, u8 oamIndex, SpriteSize size, SpriteColorFormat colorFormat, bool subScreen) {
    auto& oam = (subScreen ? spritesOAMSub : spritesOAM);
    assert(oamIndex < spritesOAMSize && oam[oamIndex].getGfxPtr() == nullptr);

    oam[oamIndex] =
        SpriteOAMSlot(
            oamAllocateGfx(
                subScreen ? &oamSub : &oamMain,
                size, colorFormat),
            size,
            colorFormat);

    const Sprite& s = getSprite(ramIndex);
    dmaCopy(s.getGfx(),
        oam[oamIndex].getGfxPtr(),
        s.getGfxLen());
    dmaCopy(s.getPal(),
        (subScreen ? SPRITE_PALETTE_SUB : SPRITE_PALETTE) + 16 * oamIndex,
        s.getPalLen());
}

void AssetManager::unloadSpriteVRAM(u8 oamIndex, bool subScreen) {
    auto& oam = (subScreen ? spritesOAMSub : spritesOAM);
    assert(oamIndex < spritesOAMSize);

    if (oam[oamIndex].getGfxPtr() == nullptr) return;

    oamFreeGfx(
        subScreen ? &oamSub : &oamMain,
        oam[oamIndex].getGfxPtr());

    oam[oamIndex].setGfxPtr(nullptr);
}

void AssetManager::unloadSpriteVRAMAll(bool subScreen) {
    for (int i = 0; i < spritesOAMSize; i++) {
        unloadSpriteVRAM(i, subScreen);
    }
}

void AssetManager::overwriteSpriteVRAM(u8 ramIndex, u8 ramOffset, u8 oamIndex, bool subScreen) {
    auto& oam = (subScreen ? spritesOAMSub : spritesOAM);
    assert(oamIndex < spritesOAMSize);

    SpriteOAMSlot& sos = oam[oamIndex];
    const Sprite& sprite = getSprite(ramIndex);
    assert(sprite.getGfx() != nullptr);

    int pixels = SPRITE_SIZE_PIXELS(sos.getSize()) >> (sos.getColorFormat() == SpriteColorFormat_16Color ? 1 : 0);
    dmaCopy(sprite.getGfx() + pixels * ramOffset, sos.getGfxPtr(), pixels);
}

void AssetManager::addSprite(u8 id, u8 oamIndex, bool subScreen, s16 x, s16 y, u8 priority) {
    auto& oam = (subScreen ? spritesOAMSub : spritesOAM);
    assert(oamIndex < spritesOAMSize);

    SpriteOAMSlot& s = oam[oamIndex];
    oamSet(subScreen ? &oamSub : &oamMain,
        id,
        x, y,
        priority,
        oamIndex,
        s.getSize(), s.getColorFormat(),
        s.getGfxPtr(),
        -1,
        false,
        false,
        false,
        false,
        false);
}

void AssetManager::changeSprite(u8 id, u8 oamIndex, bool subScreen) {
    auto& oam = (subScreen ? spritesOAMSub : spritesOAM);
    assert(oamIndex < spritesOAMSize);

    SpriteOAMSlot& s = oam[oamIndex];
    oamSetGfx(subScreen ? &oamSub : &oamMain, id, s.getSize(), s.getColorFormat(), s.getGfxPtr());
}

void AssetManager::moveSprite(u8 id, bool subScreen, s16 x, s16 y) {
    oamSetXY(subScreen ? &oamSub : &oamMain, id, x, y);
}

void AssetManager::hideSprite(u8 id, bool subScreen, bool hide) {
    oamSetHidden(subScreen ? &oamSub : &oamMain, id, hide);
}

void AssetManager::removeSprite(u8 id, bool subScreen) {
    oamClearSprite(subScreen ? &oamSub : &oamMain, id);
}

void AssetManager::removeAllSprites(bool subScreen) {
    oamClear(subScreen ? &oamSub : &oamMain, 0, 0);
}

Background::Background(const unsigned int *newGfx, unsigned int newGfxLen,
                    const short unsigned int *newMap, unsigned int newMapLen,
                    const short unsigned int *newPal, unsigned int newPalLen) :
        gfxLen(newGfxLen),
        mapLen(newMapLen),
        palLen(newPalLen){

    gfx = std::make_unique<u8[]>(newGfxLen);
    dmaCopy(newGfx, gfx.get(), newGfxLen);

    map = std::make_unique<u8[]>(newMapLen);
    dmaCopy(newMap, map.get(), newMapLen);

    pal = std::make_unique<u8[]>(newPalLen);
    dmaCopy(newPal, pal.get(), newPalLen);

}

Sprite::Sprite(const unsigned int newGfx[], unsigned int newGfxLen,
                    const short unsigned int newPal[], unsigned int newPalLen) {
    gfx = std::make_unique<u8[]>(newGfxLen);
    dmaCopy(newGfx, gfx.get(), newGfxLen);
    gfxLen = newGfxLen;


    pal = std::make_unique<u8[]>(newPalLen);
    dmaCopy(newPal, pal.get(), newPalLen);
    palLen = newPalLen;
}

SpriteOAMSlot::SpriteOAMSlot(u16* newGfxPtr, SpriteSize newSize, SpriteColorFormat newColorFormat) {
    gfxPtr = newGfxPtr;
    size = newSize;
    colorFormat = newColorFormat;
}