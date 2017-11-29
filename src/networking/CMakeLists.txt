
cmake_minimum_required(VERSION 2.8)

add_library(Networking
        world_updater_factory.cpp
        game_server.cpp
        sdl_client.cpp
        sdl_server.cpp
        message.cpp
        server_connection.cpp
        client_connection.cpp
        )

