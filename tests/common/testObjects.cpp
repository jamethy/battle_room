#include "battle_room/common/object.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::vector;
using std::string;

namespace BattleRoom {

TEST(Test_getUniqueId, typical) {

    Object obj1(UniqueId::generateNewLocalId());
    Object obj2(UniqueId::generateNewLocalId());

    Object obj1b = obj1;

    EXPECT_EQ(obj1.getUniqueId(), obj1b.getUniqueId());
    EXPECT_NOT_EQ(obj1.getUniqueId(), obj1b.getUniqueId());
    EXPECT_NOT_EQ(obj1.getUniqueId(), obj2.getUniqueId());
    EXPECT_NOT_EQ(obj1b.getUniqueId(), obj2.getUniqueId());

}
