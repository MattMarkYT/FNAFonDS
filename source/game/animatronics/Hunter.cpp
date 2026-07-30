#include "animatronics/Hunter.hpp"

using namespace game::animatronics;

u8 Hunter::getNextMove() {
    const auto positions = movePositions.find(getPosition());

    if (positions != movePositions.end())
        return positions->second;

    return invalidPosition;  // If animatronic disappears, this fail-safe occurred due to incorrect movePositions
}

void Hunter::movementOpportunity() {
    if (canMove && moveChance()) {
        startCountdown();
    }
}

void Hunter::move() {
    if (!bufferedMove) return;

    if (getPosition() != getFinalPosition())
        move();
    else
        doorMove();
}

void Hunter::startCountdown() {

}

void Hunter::countdownDone() {

}