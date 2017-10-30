#ifndef SCREEN_ANCHOR_H
#define SCREEN_ANCHOR_H

#include <string>

namespace BattleRoom {

    enum ScreenAnchor {
        TopLeft, TopRight, BottomLeft, BottomRight, Center
    }; // ScreenAnchor enum

    ScreenAnchor anchorFromStr(std::string str);

} // BattleRoom namespace
#endif // SCREEN_ANCHOR_H
