#ifndef FNAFONDS_HUNTER_H
#define FNAFONDS_HUNTER_H

#include <nds.h> // For u8 type
#include <unordered_map>
#include "Animatronic.hpp"

namespace game {
    namespace animatronics {
        class Hunter : public Animatronic {
            bool canMove = true;        // It fails every movement opportunity if this is false
            bool bufferedMove = false;  // Once countdown is done, hunter is waiting to move
            u16 moveCountdown = 0;
            std::unordered_map<u8, u8> movePositions{};

            void setMoveCountdown(u16 countdown) {
                moveCountdown = countdown;
            }
            u8 getNextMove();

            void movementOpportunity() override;
            void move() override;

            void startCountdown();
            void countdownDone();


        };
    }
}


#endif //FNAFONDS_HUNTER_H