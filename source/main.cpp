
#include "game/save/Save.hpp"
#include <nds/arm9/dldi.h>
#include "ui/mainmenu.hpp"

bool initFS(int argc, char **argv) {
    if (!fatInitDefault())
    {
        return false;
    }
    if (argc == 0)
    {
        return false;
    }
    if (argv[0] == nullptr)
    {
        return false;
    }
    if (strlen(argv[0]) < 4)
    {
        return false;
    }

    return Save::setSavePath(argv[0]);

}

int main(int argc, char **argv) {
    if (initFS(argc, argv))
        Save::setSaveInitFailed();
    if (!Save::loadGame())
        Save::setSaveInitFailed();

    while (true) {
        mainmenu();

        scanKeys();
        u16 keys_held = keysHeld();

        if (keys_held & KEY_SELECT)
            break;
    }

}
