cmake_minimum_required(VERSION 2.8)

add_library(Common 
        string_utils.cpp
        file_utils.cpp
        resource_descriptor.cpp
        pixel.cpp
        rel_pixel.cpp
        unique_id.cpp
        vector3d.cpp
        quaternion.cpp
        input.cpp
        inputs.cpp
        input_gatherer.cpp
        color.cpp
        drawable_object.cpp
        drawable_text.cpp
    )
