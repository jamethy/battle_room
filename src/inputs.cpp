#include "inputs.h"

using std::vector;

namespace BattleRoom {

    void Inputs::addInput(Input input) {
        m_inputs.push_back(input);
    }

    vector<Input>::iterator Inputs::begin() {
        return m_inputs.begin();
    }

    vector<Input>::iterator Inputs::end() {
        return m_inputs.end();
    }

} // BattleRoom namespace
