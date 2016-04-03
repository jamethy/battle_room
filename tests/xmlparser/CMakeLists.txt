
include_directories( ${CMAKE_SOURCE_DIR}/src/xmlparser )

add_executable(runXmlParserTests 
                    testParserHelperFuncions.cpp 
                    testXmlParser.cpp
                    testAttributeSet.cpp
               )

target_link_libraries(runXmlParserTests gtest gmock gtest_main XmlParser)

add_test( NAME XmlParserTests COMMAND runXmlParserTests )

