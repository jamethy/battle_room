#include "battleroom/AttributeSet.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace XmlParser {

////////////////////////////////////////////////////////////////////////////////
// readEntireFile Tests
////////////////////////////////////////////////////////////////////////////////
TEST(Test_getString, defaultvalue) {
    AttributeSet attrs("stringtest=\"MyString\"");
    std::string expected = "defaultvalue";
    std::string actual = attrs.getString("notinthere","defaultvalue");
    EXPECT_EQ(expected, actual);
}

TEST(Test_getInt, defaultvalue) {
    AttributeSet attrs("inttest=\"123\"");
    int expected = -1;
    int actual = attrs.getInt("notintthere",-1);
    EXPECT_EQ(expected, actual);
}

TEST(Test_getDouble, defaultvalue) {
    AttributeSet attrs("doubletest=\"12.3\"");
    double expected = -1.0;
    double actual = attrs.getDouble("notintthere",-1.0);
    EXPECT_EQ(expected, actual);
}

TEST(Test_getIntPoint, defaultvalue) {
    AttributeSet attrs("intptest=\"(123,456)\"");
    IntPoint expected(-1,-1);
    IntPoint actual = attrs.getIntPoint("notintthere",IntPoint(-1,-1));
    EXPECT_EQ(expected.a(), actual.a());
    EXPECT_EQ(expected.b(), actual.b());
}

TEST(Test_getDoublePoint, defaultvalue) {
    AttributeSet attrs("dptest=\"(12.3,45.6)\"");
    DoublePoint expected(-1.0,-1.0);
    DoublePoint actual = attrs.getDoublePoint("notintthere",DoublePoint(-1.0,-1.0));
    EXPECT_EQ(expected.a(), actual.a());
    EXPECT_EQ(expected.b(), actual.b());
}

TEST(Test_getString, success) {
    AttributeSet attrs("stringtest=\"MyString\"");
    std::string expected = "MyString";
    std::string actual = attrs.getString("stringtest","defaultvalue");
    EXPECT_EQ(expected, actual);
}

TEST(Test_getInt, success) {
    AttributeSet attrs("inttest=\"123\"");
    int expected = 123;
    int actual = attrs.getInt("inttest",-1);
    EXPECT_EQ(expected, actual);
}

TEST(Test_getDouble, success) {
    AttributeSet attrs("doubletest=\"12.3\"");
    double expected = 12.3;
    double actual = attrs.getDouble("doubletest",-1.0);
    EXPECT_EQ(expected, actual);
}

TEST(Test_getIntPoint, success) {
    AttributeSet attrs("intptest=\"(123,456)\"");
    IntPoint expected(123,456);
    IntPoint actual = attrs.getIntPoint("intptest",IntPoint(-1,-1));
    EXPECT_EQ(expected.a(), actual.a());
    EXPECT_EQ(expected.b(), actual.b());
}

TEST(Test_getDoublePoint, success) {
    AttributeSet attrs("dptest=\"(12.3,45.6)\"");
    DoublePoint expected(12.3,45.6);
    DoublePoint actual = attrs.getDoublePoint("dptest",DoublePoint(-1.0,-1.0));
    EXPECT_EQ(expected.a(), actual.a());
    EXPECT_EQ(expected.b(), actual.b());
}

} // XmlParser namespace
