#ifndef INPUT_GATHERER_H
#define INPUT_GATHERER_H

#include "battle_room/common/inputs.h"

namespace BattleRoom {

/**
 * \brief Gathers inputs from the display windows
 */
    class InputGatherer {

    public:

        /**
         * \brief Gets Inputs and clears current stash
         * \return Inputs object containing inputs
         */
        static Inputs getAndClearInputs();


        /**
         * \brief Adds input to the input stash
         * \param input Input to add to the stash
         */
        static void addInput(Input input);

    }; // InputGatherer class
} // BattleRoom namespace
#endif // INPUT_GATHERER_H
