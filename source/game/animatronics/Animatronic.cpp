#include <cstdlib>
#include "animatronics/Animatronic.hpp"

using namespace game::animatronics;

/**
 * @class Animatronic
 * @author MattMark
 *
 * This class is used as a Base class for all animatronics
 *
 */

Animatronic::Animatronic(u8 aiLevel, u8 startingPosition, u8 finalPosition, u8 blockedPosition,
                        int movementTime, int movementTimeRemainder) {
    this->aiLevel = aiLevel;
    this->position = startingPosition;
    this->finalPosition = finalPosition;
    this->blockedPosition = blockedPosition;
    this->movementTime = movementTime;
    this->movementTimeRemainder = movementTimeRemainder;
    this->moveTimer = 0;
}

bool Animatronic::moveChance() const {
    return aiLevel > rand() % 20;
}

void Animatronic::movementOpportunity() {
    if (moveChance()) {
        if (position != finalPosition)
            move();
        else
            doorMove();
    }
}

