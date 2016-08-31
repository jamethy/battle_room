#ifndef INPUTS_H
#define INPUTS_H

#include "battle_room/common/input.h"

namespace BattleRoom {

// TODO fill class
/**
 * \brief User inputs from the screen
 */
class Inputs {

public:

    void addInput(Input input);
    void addQuitEvent();

    bool containsQuitEvent() const;

    std::vector<Input>& getInputs();

    void clear();

private:

    std::vector<Input> m_inputs;
    bool m_quit = false; ///< A quit event has been triggered

}; // Inputs class
} // BattleRoom namespace
#endif // INPUTS_H
