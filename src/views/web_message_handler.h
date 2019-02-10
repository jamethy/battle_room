//
// Created by james on 1/19/19.
//

#ifndef BATTLE_ROOM_WEBMESSAGEHANDLER_H
#define BATTLE_ROOM_WEBMESSAGEHANDLER_H

#include <string>

namespace BattleRoom {

    struct WebMessageResponse {
        int statusCode;
        std::string message;
        static const int SUCCESS_CODE = 200;
        static const int NOT_FOUND_CODE = 404;
    };


    class WebMessageHandler {
    public:

        virtual WebMessageResponse onMessage(const std::string &message) = 0;

    }; // WebMessageHandler class
} // BattleRoom namespace
#endif //BATTLE_ROOM_WEBMESSAGEHANDLER_H
