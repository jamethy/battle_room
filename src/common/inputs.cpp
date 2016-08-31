#include "battle_room/common/inputs.h"

namespace BattleRoom {

void Inputs::addInput(Input input) {
    m_inputs.push_back(input);
}

void Inputs::addQuitEvent() {
    m_quit = true;
}

bool Inputs::containsQuitEvent() const {
    return m_quit;
}

std::vector<Input>& Inputs::getInputs() {
    return m_inputs;
}

void Inputs::clear() {
    m_inputs.clear();
}

} // BattleRoom namespace
