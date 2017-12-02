
cmake_minimum_required(VERSION 2.8)

add_library(Networking
        world_updater_factory.cpp
        sdl_network_helper.cpp
        sdl_client.cpp
        sdl_server.cpp
        message.cpp
        server_connection.cpp
        client_connection.cpp
        )

