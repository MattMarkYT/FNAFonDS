#ifndef FNAFONDS_COVEDWELLER_H
#define FNAFONDS_COVEDWELLER_H
#include "Animatronic.hpp"

namespace game {
    namespace animatronics {
        /**
         * @class CoveDweller
         * @brief Animatronics who stay in one spot until they charge (like Foxy)
         * @author MattMark
         */
        class CoveDweller : public Animatronic {
            bool canMove = true;   // It fails every movement opportunity if this is false

            void move() override;
            void doorMove() override;

            /**
             * @brief This starts a countdown. When it's done, the animatronic can move
             */
            void startCountdown();
            /**
             * @brief This stops any countdown and the animatronic can't move
             */
            void stopCountdown();
            /**
             * @brief This runs when the animatronic leaves their post
             */
            void leaveCove();

        };
    }
}


#endif //FNAFONDS_COVEDWELLER_H