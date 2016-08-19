cmake_minimum_required(VERSION 2.8)

add_library(Common 
        string_utils.cpp
        file_utils.cpp
        resource_descriptor.cpp
        pixel.cpp
        position.cpp
        object.cpp
        vector3d.cpp
        quaternion.cpp
    )
