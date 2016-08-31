cmake_minimum_required(VERSION 2.8)

add_library(Common 
        string_utils.cpp
        file_utils.cpp
        resource_descriptor.cpp
        pixel.cpp
        rel_pixel.cpp
        position.cpp
        unique_id.cpp
        object.cpp
        vector3d.cpp
        quaternion.cpp
        input.cpp
        inputs.cpp
        input_gatherer.cpp
    )
