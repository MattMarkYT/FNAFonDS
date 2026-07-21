#include "animatronics/CoveDweller.hpp"

using namespace game::animatronics;

void CoveDweller::move() {
    u8 position = getPosition() + 1;
    setPosition(position);
    if (position == getFinalPosition()) {
        leaveCove();
    }
}

void CoveDweller::doorMove() {
    if (getTargetDoor()->getClosed()) {
        setPosition(getBlockedPosition());
    }
    else {
        setPosition(getPosition() + 1);
    }
}

void CoveDweller::startCountdown() {

}

void CoveDweller::stopCountdown() {

}

void CoveDweller::leaveCove() {

}


