#include "battleroom/XmlParser.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>

namespace XmlParser {

////////////////////////////////////////////////////////////////////////////////
// TopLevel Tests
////////////////////////////////////////////////////////////////////////////////
TEST(test_TopLevel, get_tag) {
    std::string expected = "Head";
    XmlItem xml = XmlItem::fromXmlString(
            "<Head />"
    );

    ASSERT_EQ((unsigned long)1,xml.getItems().size());
    std::string actual = xml.getItems()[0].getTag();
    EXPECT_EQ(expected, actual);
}

TEST(test_TopLevel, get_attribute) {
    std::string expected = "wowza";
    XmlItem xml = XmlItem::fromXmlString(
            "<Head name=\"wowza\" />"
    );

    ASSERT_EQ((unsigned long)1,xml.getItems().size());
    std::string actual = xml.getItems()[0]
                            .getAttributeSet()
                            .getString("name","defaultvalue");
    EXPECT_EQ(expected, actual);
}

////////////////////////////////////////////////////////////////////////////////
// SecondLevel Tests
////////////////////////////////////////////////////////////////////////////////
TEST(test_TopLevel, get_sub) {
    std::string expectedTag = "body";
    std::string expectedAttr = "pup";
    XmlItem xml = XmlItem::fromXmlString(
            "<Head name=\"wowza\"> <body stuff=\"pup\" /></Head>"
    );

    ASSERT_EQ((unsigned long)1,xml.getItems().size());
    std::vector<XmlItem> subitems = xml.getItems()[0].getItems();

    ASSERT_EQ((unsigned long)1,subitems.size());
    std::string actualTag = subitems[0].getTag();
    std::string actualAttr = subitems[0]
                            .getAttributeSet()
                            .getString("stuff","defaultvalue");
    EXPECT_EQ(expectedTag, actualTag);
    EXPECT_EQ(expectedAttr, actualAttr);
}

////////////////////////////////////////////////////////////////////////////////
// XmlStringFromFile Tests                                                      
////////////////////////////////////////////////////////////////////////////////
TEST(Test_filterXmlString, simpleTest) {

    std::string filename = std::string(TEST_FILES_DIR) + "/simplexml.xml";
    XmlItem actual = XmlItem::fromXmlFile(filename);

    // root
    EXPECT_EQ("root", actual.getTag());

    // level 1
    ASSERT_EQ((unsigned long)1, actual.getItems().size());
    XmlItem lvl1 = actual.getItems()[0];
    EXPECT_EQ("Head",lvl1.getTag());
    EXPECT_EQ("myHead",lvl1
                        .getAttributeSet()
                        .getString("name","defaultvalue"));

    // level 2
    ASSERT_EQ((unsigned long)1, lvl1.getItems().size());
    XmlItem lvl2 = lvl1.getItems()[0];
    EXPECT_EQ("body",lvl2.getTag());
    EXPECT_EQ("myBody",lvl2
                        .getAttributeSet()
                        .getString("type","defaultvalue"));

    // level 3
    EXPECT_EQ((unsigned long)0, lvl2.getItems().size());
}


} // XmlParser namespace

