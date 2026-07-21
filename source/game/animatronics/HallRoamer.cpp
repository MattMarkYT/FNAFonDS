#include <cstdlib>
#include "animatronics/HallRoamer.hpp"

using namespace game::animatronics;

/**
 * @brief Hall Roamers have 2 possible next positions. Choose one and move there
 */
void HallRoamer::move() {
    const auto positions = movePositions.find(getPosition());
    u8 nextPosition;

    if (positions != movePositions.end())
        nextPosition = positions->second[rand() % 2];
    else
        nextPosition = invalidPosition;  // If animatronic disappears, this fail-safe occurred due to incorrect movePositions

    setPosition(nextPosition);
}

void HallRoamer::doorMove() {
    if (getTargetDoor() == nullptr) return;

    if (getTargetDoor()->getClosed())
        setPosition(getBlockedPosition());
    else
        setPosition(officePosition);

}
