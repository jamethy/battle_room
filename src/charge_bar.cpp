//
// Created by james on 2/2/19.
//

#include "charge_bar.h"

namespace BattleRoom {

    ChargeBar::ChargeBar(meters width) : m_percentCharged(0), m_width(width) { }

    double ChargeBar::getPercentCharged() const {
        return m_percentCharged;
    }

    void ChargeBar::setPercentCharged(double percentCharged) {
        m_percentCharged = percentCharged;
    }

    meters ChargeBar::getWidth() const {
        return m_width;
    }

    void ChargeBar::setWidth(meters width) {
        m_width = width;
    }

    std::string ChargeBar::getType() const {
        return "ChargeBar";
    }
}// BattleRoom namespace
