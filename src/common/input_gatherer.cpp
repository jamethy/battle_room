#include "battle_room/common/input_gatherer.h"

namespace BattleRoom {

Inputs m_inputs; ///< Current stash of inputs
bool m_quitEvent = false; ///< Current state of quitting

Inputs InputGatherer::getAndClearInputs() {

    Inputs copy = m_inputs;
    m_inputs = Inputs();
    return copy;
}

void InputGatherer::addInput(Input input) {

    m_inputs.addInput(input);

}

void InputGatherer::addQuitEvent() {
    m_quitEvent = true;
}

bool InputGatherer::containsQuitEvent() {
    return m_quitEvent;
}


} // BattleRoom namespace
