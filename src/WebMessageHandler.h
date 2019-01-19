//
// Created by james on 1/19/19.
//

#ifndef PROJECT_DEATHBLADE_WEBMESSAGEHANDLER_H
#define PROJECT_DEATHBLADE_WEBMESSAGEHANDLER_H

#include <string>

namespace BattleRoom {

    class WebMessageHandler {
    public:
        virtual std::string onMessage(const std::string &message) = 0;

    }; // WebMessageHandler class
} // BattleRoom namespace
#endif //PROJECT_DEATHBLADE_WEBMESSAGEHANDLER_H
