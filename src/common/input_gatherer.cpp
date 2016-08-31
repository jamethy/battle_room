#include "battle_room/common/input_gatherer.h"

namespace BattleRoom {

Inputs m_inputs; ///< Current stash of inputs

Inputs InputGatherer::getAndClearInputs() {

    Inputs copy = m_inputs;
    m_inputs.clear();
    return copy;
}

void InputGatherer::addInput(Input input) {

    m_inputs.addInput(input);

}

void InputGatherer::addQuitEvent() {
    m_inputs.addQuitEvent();
}


} // BattleRoom namespace
