#include "game/animatronics/CoveDweller.hpp"

using namespace game::animatronics;

void CoveDweller::movementOpportunity() {
    if (canMove && getPosition() < getFinalPosition() && moveChance()) {
        move();
    }
}

void CoveDweller::move() {
    u8 position = getPosition() + 1;
    setPosition(position);
    if (position == getFinalPosition()) {
        leaveCove();
    }
}

void CoveDweller::startCountdown() {

}

void CoveDweller::countdownDone() {
    canMove = true;
}

void CoveDweller::stopCountdown() {
    canMove = false;
}

void CoveDweller::leaveCove() {

}


