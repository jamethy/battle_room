#ifndef GAMEENUMS_H
#define GAMEENUMS_H

namespace db {

/*!
 * \brief The ZPlane enum labels which depth plane an object is on
 */
enum ZPlane {
    Floor = 0,  //!< Background plane
    Player = 1, //!< Battle plane
    Gui = 2     //!< Fake plane for the GUI (could do something fun?)
};
}

#endif // GAMEENUMS_H
