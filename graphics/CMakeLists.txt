project(graphics)


add_library(battleroom_graphics SHARED
        object_handler.h object_handler.cpp
        graphics_layer.h graphics_layer.cpp
        player_object.h player_object.cpp
        star_object.h star_object.cpp
        )

