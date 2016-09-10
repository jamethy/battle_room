
add_executable(runAnimationTests
                    testCamera.cpp
               )

target_link_libraries(runAnimationTests gtest gmock gtest_main Common Graphics)

add_test( NAME AnimationTests COMMAND runAnimationTests )
