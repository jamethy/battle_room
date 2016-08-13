
add_executable(runAnimationTests
                    testAnimation.cpp
               )

target_link_libraries(runAnimationTests gtest gmock gtest_main Common Animation)

add_test( NAME AnimationTests COMMAND runAnimationTests )
