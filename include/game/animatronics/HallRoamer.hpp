#ifndef FNAFONDS_HALLROAMER_H
#define FNAFONDS_HALLROAMER_H

#include <nds.h> // For u8 type
#include <unordered_map>
#include "Animatronic.hpp"

namespace game {
    namespace animatronics {
        class HallRoamer : public Animatronic {
            u8 closeFar;

            /**
             * Implements the Hall Roamer successful movement
             */
            void move() override;
            /**
             * Implements the Hall Roamer successful door move
             */
            void doorMove() override;
        };
    }
}

#endif //FNAFONDS_HALLROAMER_H