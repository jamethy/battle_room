//
// Created by james on 1/19/19.
//

#ifndef BATTLE_ROOM_WEBMESSAGEHANDLER_H
#define BATTLE_ROOM_WEBMESSAGEHANDLER_H

#include <string>

namespace BattleRoom {

    class WebMessageHandler {
    public:
        virtual std::string onMessage(const std::string &message) = 0;

    }; // WebMessageHandler class
} // BattleRoom namespace
#endif //BATTLE_ROOM_WEBMESSAGEHANDLER_H
