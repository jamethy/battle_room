
cmake_minimum_required(VERSION 2.8)

add_library(Game
        game_object.cpp
        game_time.cpp
        world.cpp
        query_world.cpp
        command_receiver.cpp
        command.cpp
        local_updating_world.cpp
        local_world_updater.cpp
        objects/ball.cpp
        objects/bullet.cpp
        objects/player.cpp
        objects/object_intersection.cpp
        )
