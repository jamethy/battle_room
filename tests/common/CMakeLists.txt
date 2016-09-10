
add_executable(runCommonTests
                    testResourceDescriptor.cpp 
                    testFileUtils.cpp 
                    testStringUtils.cpp
                    testQuaternion.cpp
                    testMisc.cpp
               )

target_link_libraries(runCommonTests gtest gmock gtest_main 
                   ${START_GROUP}
                   Common 
                   Animation
                   ${END_GROUP}
               )

add_test( NAME CommonTests COMMAND runCommonTests )
