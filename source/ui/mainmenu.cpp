#include "ui/mainmenu.hpp"

using namespace ui;
// Backgrounds
constexpr int fred1 = 0;
// Sprites
constexpr int staticSprite = 0;

void loadAssets(AssetManager& scene) {
    scene.showLoadSprite();

    scene.loadBackground(fred1, fred1Tiles, fred1TilesLen, fred1Map, fred1MapLen, fred1Pal, fred1PalLen);
    scene.loadSpriteRAM(staticSprite, staticTiles, staticTilesLen, staticPal, staticPalLen);

    scene.hideLoadSprite();
}
void setupUI(AssetManager& scene) {
    scene.loadSpriteVRAM(staticSprite, staticSprite, SpriteSize_64x64, SpriteColorFormat_16Color, false);

    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 3; y++)
            scene.addSprite(x+y * 4, staticSprite, false, x * 64, y * 64, 0);
    oamUpdate(&oamMain);

    scene.showBackground(fred1, 0);
}

void mainmenu() {

    AssetManager scene;
    loadAssets(scene);
    setupUI(scene);

    int bruh = 0;

    while (true) {
        swiWaitForVBlank();

        scene.overwriteSpriteVRAM(staticSprite, bruh >> 1, staticSprite, false);

        bruh++;
        if (bruh >= 6) bruh = 0;
        for (int x = 0; x < 4; x++)
            for (int y = 0; y < 3; y++)
                scene.hideSprite(x+y * 4, false, (bruh & 1) != 0);

        oamUpdate(&oamMain);

        scanKeys();
        u16 keys_held = keysHeld();

        if (keys_held & KEY_START)
            break;
    }

}