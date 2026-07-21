#ifndef FNAFONDS_ANIMATRONIC_HPP
#define FNAFONDS_ANIMATRONIC_HPP

#include <nds.h> // For u8 type
#include "office/Door.hpp"

namespace game {
    namespace animatronics {
        /**
         * @class Animatronic
         * @brief Basic Animatronic class
         * @author MattMark
         *
         * This class is used as a Base class for all animatronics
         */
        class Animatronic {

            u8 aiLevel;                 // AI Level 0-20
            u8 position;                // Current Position
            u8 finalPosition;           // Position to do alt door move
            u8 blockedPosition;         // Position to return to when blocked
            int movementTime;           //
            int movementTimeRemainder;  //
            int moveTimer = 0;          //
            Door* targetDoor = nullptr;

        public:
            static constexpr u8 officePosition = -1;
            static constexpr u8 invalidPosition = -2;

            virtual ~Animatronic() = default;

            Animatronic(u8 aiLevel, u8 position, u8 finalPosition, u8 blockedPosition,
                        int movementTime, int movementTimeRemainder);

            u8 getPosition() { return position; }
            void setPosition(u8 newPosition) { position = newPosition; }
            u8 getFinalPosition() { return finalPosition; }
            u8 getBlockedPosition() { return position; }
            Door* getTargetDoor() { return targetDoor; }

            /**
             * @brief This is run every movement interval
             */
            virtual void movementOpportunity();

        private:
            /**
             * @brief Rolls a chance of AI Level / 20 for successful movement
             * @return boolean representing success
             */
            bool moveChance() const;
            /**
             * @brief Will implement animatronic's successful movement
             */
            virtual void move();
            /**
             * @brief Will implement animatronic's successful movement at its final position (at the door)
             */
            virtual void doorMove();

        };
    }
}

#endif //FNAFONDS_ANIMATRONIC_HPP