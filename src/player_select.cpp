//
// Created by james on 2/2/19.
//

#include "include/cef_parser.h"
#include "include/cef_values.h"
#include "player_select.h"
#include "logger.h"

namespace BattleRoom {

    void PlayerSelect::update(const Player *player) {
        auto frame = player->getAnimation().getFrame(player->getAnimationState());

        setLocation(player->getLocation());
        m_playerWidth = frame.getWidth();
        m_playerHeight = frame.getHeight();
        m_jumpCharge = player->getJumpCharge();
        m_gunCharge = player->getGunCharge();
    }

    std::string PlayerSelect::getType() const {
        return "PlayerSelect";
    }

    std::string PlayerSelect::getJson(Camera* camera, View* view) const {
        int viewWidth = view->getViewWidth();
        int viewHeight = view->getViewHeight();
        Pixel viewTopLeft = view->getTopLeft();

        auto json = CefDictionaryValue::Create();
        auto type = CefValue::Create();
        type->SetString(getType());
        json->SetValue("type", type);

        auto props = CefDictionaryValue::Create();

        auto uniqueId = CefValue::Create();
        uniqueId->SetString(getUniqueId().toString());
        props->SetValue("uniqueId", uniqueId);

        auto rel = camera->fromLocation(getLocation());

        auto x = CefValue::Create();
        x->SetDouble(rel.getCol() * viewWidth + viewTopLeft.getCol());
        props->SetValue("x", x);

        auto y = CefValue::Create();
        y->SetDouble(rel.getRow() * viewHeight + viewTopLeft.getRow());
        props->SetValue("y", y);

        auto playerWidth = CefValue::Create();
        playerWidth->SetDouble(viewWidth * camera->zeroPlaneLength(m_playerWidth));
        props->SetValue("playerWidth", playerWidth);

        auto playerHeight = CefValue::Create();
        playerWidth->SetDouble(viewWidth * camera->zeroPlaneLength(m_playerHeight));
        props->SetValue("playerHeight", playerWidth);

        auto jumpCharge = CefValue::Create();
        jumpCharge->SetDouble(m_jumpCharge);
        props->SetValue("jumpCharge", jumpCharge);

        auto gunCharge = CefValue::Create();
        gunCharge->SetDouble(m_gunCharge);
        props->SetValue("gunCharge", gunCharge);

        json->SetDictionary("props", props);
        auto value = CefValue::Create();
        value->SetDictionary(json);
        return CefWriteJSON(value, JSON_WRITER_DEFAULT).ToString();
    }
}// BattleRoom namespace
