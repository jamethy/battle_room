cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_executable(run_animation run_animation.cpp )

target_link_libraries(run_animation
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_gfx_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    Common
)

