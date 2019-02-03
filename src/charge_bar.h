//
// Created by james on 2/2/19.
//

#ifndef BATTLE_ROOM_CHARGE_BAR_H
#define BATTLE_ROOM_CHARGE_BAR_H

#include "game_ui_element.h"

namespace BattleRoom {

    class ChargeBar : public GameUIElement {
    public:

        explicit ChargeBar(meters width);

        // getters and setters
        double getPercentCharged() const;

        void setPercentCharged(double percentCharged);

        meters getWidth() const;

        void setWidth(meters width);

        // inherited
        std::string getType() const override;

    private:
        double m_percentCharged;
        meters m_width;
    }; // charge_bar class
}// BattleRoom namespace
#endif //PROJECT_BATTLE_ROOM_CHARGE_BAR_H
