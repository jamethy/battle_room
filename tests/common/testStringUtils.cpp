
#include "battle_room/common/string_utils.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::string;
using std::vector;

namespace BattleRoom {

TEST(Test_toLower, typical) {

    string a = "Hello World.\n";
    
    EXPECT_STREQ("hello world.\n", toLower(a).c_str());
}


TEST(Test_match, typical) {

    string a = "Hello World.\n";
    string b = "helLo WorlD.\n";
    
    EXPECT_EQ(true, keyMatch(a,b));
}

TEST(Test_split, typical) {
    
    string a = "This, is, split by, commas";
    vector<string> as = split(a,',');

    ASSERT_EQ(4u, as.size());
    EXPECT_STREQ("This", as[0].c_str());
    EXPECT_STREQ(" is", as[1].c_str());
    EXPECT_STREQ(" split by", as[2].c_str());
    EXPECT_STREQ(" commas", as[3].c_str());
}

} // BattleRoom namespace

