
cmake_minimum_required(VERSION 2.8)

add_library ( Common 
        animation.cpp
        animation_handler.cpp
        color.cpp
        drawable_object.cpp
        drawable_text.cpp
        file_utils.cpp
        frame.cpp
        input.cpp
        input_gatherer.cpp
        inputs.cpp
        pixel.cpp
        quaternion.cpp
        rel_pixel.cpp
        resource_descriptor.cpp
        string_utils.cpp
        unique_id.cpp
        vector2d.cpp
        vector3d.cpp
        view_interface.cpp
        units.cpp
        projection1d.cpp
        boundary.cpp
        boundary_set.cpp
        circle_boundary.cpp
        box_boundary.cpp
        sat_intersection.cpp
)
