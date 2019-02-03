//
// Created by james on 2/2/19.
//

#ifndef BATTLE_ROOM_CHARGE_BAR_H
#define BATTLE_ROOM_CHARGE_BAR_H

#include "game_ui_element.h"
#include "player.h"

namespace BattleRoom {

    class PlayerSelect : public GameUIElement {
    public:

        void update(const Player *player);

        // inherited
        std::string getType() const override;
        std::string getJson(Camera* camera, View* view) const override;

    private:
        meters m_playerWidth = 0;
        meters m_playerHeight = 0;
        double m_jumpCharge = 0; // 0-1
        double m_gunCharge = 0; // 0-1
    }; // charge_bar class
}// BattleRoom namespace
#endif //PROJECT_BATTLE_ROOM_CHARGE_BAR_H
