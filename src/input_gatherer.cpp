#include "input_gatherer.h"

namespace BattleRoom {

    Inputs m_inputs; ///< Current stash of inputs

    Inputs InputGatherer::getAndClearInputs() {

        Inputs copy = m_inputs;
        m_inputs = Inputs();
        return copy;
    }

    void InputGatherer::addInput(Input input) {
        m_inputs.addInput(input);
    }

} // BattleRoom namespace
