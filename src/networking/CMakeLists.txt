
cmake_minimum_required(VERSION 2.8)

add_library(Networking
        network_world_updater.cpp
        world_updater_factory.cpp
        game_server.cpp
        messages/message_header.cpp
        sdl_client.cpp
        )

