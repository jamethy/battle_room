
cmake_minimum_required(VERSION 2.8)

add_library ( Game
        game_interface.cpp
        game_object.cpp
        game_world.cpp
        server_client_factory.cpp
        server_factory.cpp
)
