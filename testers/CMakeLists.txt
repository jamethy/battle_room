

link_directories(${CMAKE_BINARY_DIR}/graphics)
link_libraries(deathblade_graphics)

add_executable(tester_graphics tester_graphics.cpp)
