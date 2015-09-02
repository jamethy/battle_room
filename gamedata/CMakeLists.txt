project(gamedata)

set( HANDLERS
    handlers/players.h
    handlers/players.cpp
    handlers/world.h
    handlers/world.cpp
    handlers/bullets.h
    handlers/bullets.cpp
)

set( OBJECTS
    objects/baseobject.h
    objects/baseobject.cpp
    objects/baseplayer.h
    objects/baseplayer.cpp
    objects/baseworld.h
    objects/baseworld.cpp
    objects/player.h
    objects/player.cpp
    objects/star.h
    objects/star.cpp
)

add_library(battleroom_gamedata SHARED
        ${OBJECTS}
        ${HANDLERS}
        playercontrol.h playercontrol.cpp
        gamehandler.h gamehandler.cpp
        )

