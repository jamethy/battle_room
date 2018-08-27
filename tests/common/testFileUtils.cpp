
#include "file_utils.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::string;
using std::vector;

namespace BattleRoom {

TEST(Test_getFileName, typical) {
    string test_file = "/path/to/test_file.txt";
    string expected = "test_file";
    string actual = getFileName(test_file);

    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(Test_getFileName, weirdExtension) {
    string test_file = "/path/to/test_file.l3txt";
    string expected = "test_file";
    string actual = getFileName(test_file);

    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(Test_getFileName, moreDots) {
    string test_file = "/path/to/test_file.middle.pjg";
    string expected = "test_file.middle";
    string actual = getFileName(test_file);

    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(Test_getExtension, typical) {
    string test_file = "/path/to/test_file.txt";
    string expected = "txt";
    string actual = getFileExtension(test_file);

    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(Test_getExtension, moreDots) {
    string test_file = "/path/to/test_file.middle.pjg";
    string expected = "pjg";
    string actual = getFileExtension(test_file);

    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(Test_getExtension, weirdExtension) {
    string test_file = "/path/to/test_file.l3txt";
    string expected = "l3txt";
    string actual = getFileExtension(test_file);

    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(Test_getFilepath, typical) {
    string test_file = "/path/to/test_file.l3txt";
    string expected = "/path/to/";
    string actual = getFilePath(test_file);

    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

} // BattleRoom namespace
