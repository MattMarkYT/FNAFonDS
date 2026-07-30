//
// Created by timothy on 7/26/26.
//

#ifndef FNAFONDS_SAVE_HPP
#define FNAFONDS_SAVE_HPP

#include <nds.h>
#include <stdio.h>
#include <fat.h>
#include <string.h>

class Save {
    static u8 state;
    static char *savePath;
    static constexpr char onNight = 7;
    static constexpr char beatGame = 1 << 3;
    static constexpr char beat6 = 1 << 4;
    static constexpr char beat420 = 1 << 5;
    static constexpr char saveInitFailed = 1 << 6;

public:
    Save() = delete;

    static u8 getNight() { return state & onNight; }
    static bool getBeatGame() { return (state & beatGame) != 0; }
    static bool getBeat6() { return (state & beat6) != 0; }
    static bool getBeat420() { return (state & beat420) != 0; }
    static bool getSaveInitFailed() { return (state & saveInitFailed) != 0; }

    static void setNight(u8 night) {
        if (night > 7) night = 7;
        night |= ~7;
        state &= night;
    }
    static void incNight() {
        if (getNight() >= 7) return;
        state += 1;
    }
    static void setBeatGame(const bool value) {
        if (value)  state |= beatGame;
        else        state &= ~beatGame;
    }
    static void setBeat6(const bool value) {
        if (value)  state |= beat6;
        else        state &= ~beat6;
    }
    static void setBeat420(const bool value) {
        if (value)  state |= beat420;
        else        state &= ~beat420;
    }
    static void setSaveInitFailed() {
        state |= saveInitFailed;
    }
    static bool setSavePath(const char *path);

    static bool saveGame();
    static bool loadGame();


};

#endif //FNAFONDS_SAVE_HPP