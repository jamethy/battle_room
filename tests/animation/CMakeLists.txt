
add_executable(runAnimationsTests 
                    testAnimationService.cpp
               )

target_link_libraries(runAnimationsTests gtest gmock gtest_main Animations)

add_test( NAME AnimationTests COMMAND runAnimationsTests )

