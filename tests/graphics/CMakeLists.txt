
add_executable(runAnimationTests
                    testCamera.cpp
               )

target_link_libraries(runAnimationTests gtest gmock gtest_main 
    ${START_GROUP}
    Common 
    Graphics
    ${END_GROUP}
    )

add_test( NAME AnimationTests COMMAND runAnimationTests )
