

link_directories(${CMAKE_BINARY_DIR}/graphics)
link_libraries(battleroom_graphics battleroom_utility)

add_executable(tester_graphics tester_graphics.cpp)
