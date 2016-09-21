#ifndef QUERY_WORLD_UPDATER_H
#define QUERY_WORLD_UPDATER_H

#include "battle_room/common/resource.h"

#include <memory>

namespace BattleRoom {

class QueryWorldUpdater : public Resource {

public:

    virtual ~QueryWorldUpdater(){}

}; // QueryWorldUpdater

typedef std::unique_ptr<QueryWorldUpdater> UniqueWorldUpdater;

} // BattleRoom namespace
#endif // QUERY_WORLD_UPDATER_H
