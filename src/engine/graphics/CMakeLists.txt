
cmake_minimum_required(VERSION 2.8)

add_library ( Graphics 
        sdl_display_window.cpp
        sdl_drawable.cpp
        sdl_drawable_image.cpp
        sdl_drawable_text.cpp
        sdl_font_manager.cpp
        sdl_helper_functions.cpp
        sdl_texture_manager.cpp
)
