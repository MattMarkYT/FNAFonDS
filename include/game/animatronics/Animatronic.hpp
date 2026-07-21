#ifndef FNAFONDS_ANIMATRONIC_HPP
#define FNAFONDS_ANIMATRONIC_HPP

#include <nds.h> // For u8 type

namespace game {
    namespace animatronics {
        /**
         * @class Animatronic
         * @brief Basic Animatronic class
         * @author MattMark
         *
         * This class is used as a Base class for all animatronics
         *
         */
        class Animatronic {

            u8 aiLevel;                 // AI Level 0-20
            u8 position;                // Current Position
            u8 finalPosition;           // Position to do alt door move
            u8 blockedPosition;         // Position to return to when blocked
            int movementTime;           //
            int movementTimeRemainder;  //
            int moveTimer = 0;          //

        public:
            virtual ~Animatronic() = default;

            Animatronic(u8 aiLevel, u8 position, u8 finalPosition, u8 blockedPosition,
                        int movementTime, int movementTimeRemainder);

        private:
            /**
             * Rolls a chance of AI Level / 20 for successful movement
             * @return boolean representing success
             */
            bool moveChance() const;

            /**
             * This will be used to check for movements every
             */
            virtual void movementOpportunity();

            virtual void move();
            virtual void doorMove();

        };
    }
}

#endif //FNAFONDS_ANIMATRONIC_HPP