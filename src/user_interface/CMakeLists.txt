
cmake_minimum_required(VERSION 2.8)

add_library(UserInterface
        menu.cpp
        pull_down_menu.cpp
        button.cpp
        game_interface.cpp
        menu_interface.cpp
        interface_factory.cpp
        camera/camera.cpp
        camera/moving_camera.cpp
        camera/z_max_camera.cpp
        camera/pyramid_camera.cpp
        camera/camera_factory.cpp
        view_position.cpp
        view.cpp
        )
