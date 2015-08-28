project(graphics)


add_library(battleroom_graphics SHARED
        object_handler.h object_handler.cpp
        camera.h camera.cpp
        graphics_layer.h graphics_layer.cpp
        animation_player.h animation_player.cpp
        animation_star.h animation_star.cpp
        animation_wall.h animation_wall.cpp
        sdl_window.h sdl_window.cpp
        sdl_animations.h sdl_animations.cpp
        )



target_link_libraries(battleroom_graphics
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_gfx_LIBRARY}
    ${SDL2_TTF_LIBRARY}
)
