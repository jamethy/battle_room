#include "battle_room/common/inputs.h"

using std::vector;

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

vector<Input>::iterator Inputs::begin() {
    return m_inputs.begin();
}

vector<Input>::iterator Inputs::end() {
    return m_inputs.end();
}

} // BattleRoom namespace
