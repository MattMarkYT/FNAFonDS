//
// Created by timothy on 7/26/26.
//

#include "Save.hpp"

u8 Save::state = 0;
char *Save::savePath = nullptr;

bool Save::setSavePath(const char *path) {
    if (path == nullptr) {
        return false;
    }
    savePath = strdup(path);

    // Replace the ".nds" extension by ".sav"
    size_t savePathLen = strlen(savePath);
    strcpy(&savePath[savePathLen - 3], "sav");
    return true;
}

bool Save::saveGame() {
    if (getSaveInitFailed()) return false;
    FILE *f = fopen(savePath, "wb");
    if (f == nullptr) {
        return false;
    }

    if (fwrite(&state, sizeof(state), 1, f) != 1) {
        return false;
    }

    if (fclose(f) != 0) {
        return false;
    }

    return true;
}

bool Save::loadGame() {
    FILE *f = fopen(savePath, "rb");
    if (f == nullptr) {
        return false;
    }

    if (fread(&state, sizeof(state), 1, f) != 1) {
        return false;
    }

    if (fclose(f) != 0) {
        return false;
    }

    return true;
}