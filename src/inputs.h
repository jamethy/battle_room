#ifndef INPUTS_H
#define INPUTS_H

#include "input.h"

namespace BattleRoom {

/**
 * \brief Container class of user inputs from the screen
 * Get this collection of inputs from InputGatherer
 */
    class Inputs {

    public:

        /**
         * \brief Add an input to the collection
         * \param input User input to add
         */
        void addInput(Input input);

        // These are used for ranged forloops
        std::vector<Input>::iterator begin();

        std::vector<Input>::iterator end();

    private:

        std::vector<Input> m_inputs; ///< Vector of inputs

    }; // Inputs class
} // BattleRoom namespace
#endif // INPUTS_H
