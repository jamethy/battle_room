
add_executable(runCommonTests
                    testResourceDescriptor.cpp 
                    testFileUtils.cpp 
                    testStringUtils.cpp
                    testQuaternion.cpp
                    testAnimation.cpp
                    testMisc.cpp
               )

target_link_libraries(runCommonTests gtest gmock gtest_main 
                   Common 
               )

add_test( NAME CommonTests COMMAND runCommonTests )


# just for boundaries
add_executable(runBoundaryTests
                    testBoundaryIntersection.cpp 
                    testBoundaryContains.cpp 
               )

target_link_libraries(runBoundaryTests gtest gmock gtest_main 
                   Common 
               )

add_test( NAME BoundaryTests COMMAND runBoundaryTests )
