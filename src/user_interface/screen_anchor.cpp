#include "battle_room/user_interface/screen_anchor.h"
#include "battle_room/common/string_utils.h"

namespace BattleRoom {

    ScreenAnchor anchorFromStr(std::string str) {
        if (keyMatch("TopLeft", str)) {
            return ScreenAnchor::TopLeft;
        } else if (keyMatch("TopRight", str)) {
            return ScreenAnchor::TopRight;
        } else if (keyMatch("BottomLeft", str)) {
            return ScreenAnchor::BottomLeft;
        } else if (keyMatch("BottomRight", str)) {
            return ScreenAnchor::BottomRight;
        } else {
            return ScreenAnchor::Center;
        }
    }
}
