#include "battle_room/common/object.h"
#include "battle_room/engine/animation/animation_handler.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::vector;
using std::string;

namespace BattleRoom {

TEST(Test_getUniqueId, typical) {

    AnimationHandler& handler = AnimationHandler::get();
    handler.setResourcePath(string(TEST_FILES_DIR) + "/");

    Object obj1(UniqueId::generateNewLocalId());
    Object obj2(UniqueId::generateNewLocalId());

    Object obj1b = obj1;

    EXPECT_TRUE(obj1.getUniqueId() == obj1b.getUniqueId());
    EXPECT_FALSE(obj1.getUniqueId() == obj2.getUniqueId());
    EXPECT_FALSE(obj1b.getUniqueId() == obj2.getUniqueId());

}

} // BattleRoom namespace
