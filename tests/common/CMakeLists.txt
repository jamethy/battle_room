
add_executable(runCommonTests
                    testResourceDescriptor.cpp 
                    testFileUtils.cpp 
               )

target_link_libraries(runCommonTests gtest gmock gtest_main Common)

add_test( NAME CommonTests COMMAND runCommonTests )
