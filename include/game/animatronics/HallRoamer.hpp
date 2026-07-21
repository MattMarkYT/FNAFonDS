#ifndef FNAFONDS_HALLROAMER_H
#define FNAFONDS_HALLROAMER_H

#include <nds.h> // For u8 type
#include <unordered_map>
#include "Animatronic.hpp"

namespace game {
    namespace animatronics {
        /**
         * @class HallRoamer
         * @brief Animatronics who roam the halls (like Bonnie or Chica)
         * @author MattMark
         */
        class HallRoamer : public Animatronic {
            u8 closeFar;
            std::unordered_map<u8, u8[2]> movePositions{};

            void move() override;
            void doorMove() override;
        };
    }
}

#endif //FNAFONDS_HALLROAMER_H