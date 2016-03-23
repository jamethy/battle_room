#include "ParserHelperFunctions.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

namespace XmlParser {

////////////////////////////////////////////////////////////////////////////////
// readEntireFile Tests
////////////////////////////////////////////////////////////////////////////////
TEST(Test_readEntireFile, noFile) {
    std::string expected = "";
    std::string actual = readEntireFile("This file does not exist.");
    EXPECT_EQ(expected, actual);
}

TEST(Test_readEntireFile, testFile) {
    std::string expected = "This file\n has three\n lines.\n";
    std::string test_file = std::string(TEST_FILES_DIR) + "/multilinefile.txt";
    std::string actual = readEntireFile(test_file);
    EXPECT_EQ(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////
// removeAllLineEndings Tests
////////////////////////////////////////////////////////////////////////////////
TEST(Test_removeAllLineEndings, singleEnd) {
    std::string expected = "HelloWorld";
    std::string actual = removeAllLineEndings("Hello\nWorld");
    EXPECT_EQ(expected, actual);
}

TEST(Test_removeAllLineEndings, twoEnds) {
    std::string expected = "HelloWorld";
    std::string actual = removeAllLineEndings("Hello\nWo\nrld");
    EXPECT_EQ(expected, actual);
}

TEST(Test_removeAllLineEndings, noEnd) {
    std::string expected = "HelloWorld";
    std::string actual = removeAllLineEndings("HelloWorld");
    EXPECT_EQ(expected, actual);
}

TEST(Test_removeAllLineEndings, emptyString) {
    std::string expected = "";
    std::string actual = removeAllLineEndings("");
    EXPECT_EQ(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////
// removeAllComments Tests
////////////////////////////////////////////////////////////////////////////////
TEST(Test_removeAllComments, noComments) {
    std::string expected = "This is a line with no comments";
    std::string actual = removeAllComments("This is a line with no comments");
    EXPECT_EQ(expected, actual);
}

TEST(Test_removeAllComments, oneComment) {
    std::string expected = "This is a comment:  end";
    std::string actual = 
            removeAllComments("This is a comment: <!-- Wowza! --> end");
    EXPECT_EQ(expected, actual);
}

TEST(Test_removeAllComments, twoComments) {
    std::string expected = ":  end";
    std::string actual = 
            removeAllComments("<!--This is a comment-->: <!-- Wowza! --> end");
    EXPECT_EQ(expected, actual);
}

TEST(Test_removeAllComments, commentception) {
    std::string expected = "end";
    std::string actual = 
            removeAllComments("<!--This is a comment: <!-- Wowza! --> -->end");
    EXPECT_NE(expected, actual);
}

TEST(Test_removeAllComments, looksLikeComment) {
    std::string expected = "<-- this looks like --> end";
    std::string actual = 
            removeAllComments("<-- this looks like --> end");
    EXPECT_EQ(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////
// expandAllSelfenclosed Tests
////////////////////////////////////////////////////////////////////////////////
TEST(Test_expandAllSelfenclosed, single) {
    std::string expected = "<head what=\"hello\" ></head>";
    std::string actual = expandAllSelfenclosed("<head what=\"hello\" />");
    EXPECT_EQ(expected, actual);
}

TEST(Test_expandAllSelfenclosed, doubleTag) {
    std::string expected = "<head what=\"hello\" ></head> <another ></another>";
    std::string actual = 
            expandAllSelfenclosed("<head what=\"hello\" /> <another />");
    EXPECT_EQ(expected, actual);
}

TEST(Test_expandAllSelfenclosed, none) {
    std::string expected = "<head what=\"hello\" ></head>";
    std::string actual = 
            expandAllSelfenclosed("<head what=\"hello\" ></head>");
    EXPECT_EQ(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////
// parseAttributes Tests
////////////////////////////////////////////////////////////////////////////////
TEST(Test_parseAttributes, One) {
    auto attrs = parseAttributes("therecanonlybeone=\"highlander\"");
    ASSERT_THAT(
        attrs,
        testing::ElementsAre(testing::Pair("therecanonlybeone","highlander"))
    );
}

TEST(Test_parseAttributes, empty) {
    auto attrs = parseAttributes("");
    ASSERT_THAT(
        attrs,
        testing::ElementsAre()
    );
}

TEST(Test_parseAttributes, ACouple) {
    auto attrs = parseAttributes("one=\"ONE\" two=\"TWO\"");
    ASSERT_THAT(
        attrs,
        testing::ElementsAre(
            testing::Pair("one","ONE"),
            testing::Pair("two","TWO"))
     );
}

TEST(Test_parseAttributes, extraSpace) {
    auto attrs = parseAttributes(" one=\"ONE\" two=\"TWO\" ");
    ASSERT_THAT(
        attrs,
        testing::ElementsAre(
            testing::Pair("one","ONE"),
            testing::Pair("two","TWO"))
     );
}

} // XmlParser namespace
