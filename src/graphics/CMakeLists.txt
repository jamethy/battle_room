
cmake_minimum_required(VERSION 2.8)

add_library(Graphics
        camera.cpp
        moving_camera.cpp
        z_max_camera.cpp
        pyramid_camera.cpp
        camera_factory.cpp
        sdl_display_window.cpp
        sdl_display_window.h
        sdl_drawable.cpp
        sdl_drawable.h
        sdl_drawable_image.cpp
        sdl_drawable_image.h
        sdl_drawable_text.cpp
        sdl_drawable_text.h
        sdl_font_manager.cpp
        sdl_font_manager.h
        sdl_helper_functions.cpp
        sdl_helper_functions.h
        sdl_texture_manager.cpp
        sdl_texture_manager.h
        view.cpp
        )
