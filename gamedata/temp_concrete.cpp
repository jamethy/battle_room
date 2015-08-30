#include "../interfaces/gamedata_interface.h"

namespace GameInterface {

class ConcreteGameData : public GameDataClass
{
public:
    ConcreteGameData(){}
    ~ConcreteGameData(){}

    void update(){}


};


UniqueGameData createGameData()
{
    return UniqueGameData(new ConcreteGameData());
}

}
