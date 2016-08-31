#ifndef INPUTS_H
#define INPUTS_H

#include "battle_room/common/input.h"

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

    /**
     * \brief Add a quit event to the collection
     * This should be called if the window is trying to close, or if
     * something has been mapped to quit the program
     */
    void addQuitEvent();

    /**
     * \brief Checks if a quit event has been added
     * \return True if the program should close
     */
    bool containsQuitEvent() const;

    // These are used for ranged forloops
    std::vector<Input>::iterator begin();
    std::vector<Input>::iterator end();

private:

    std::vector<Input> m_inputs; ///< Vector of inputs
    bool m_quit = false; ///< A quit event has been triggered

}; // Inputs class
} // BattleRoom namespace
#endif // INPUTS_H
