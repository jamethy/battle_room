# battle_room
The Battle Room from Ender's Game!

# Getting Started

To build the project create a folder next to _battle\_room_, maybe called _build_ and run the following
```shell
cmake -DCMAKE_BUILD_TYPE=Release ../battle_room
make
```

This will make 

# Building in Linux
The packages required in Ubuntu include:

```shell
cmake build libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-gfx-dev libsdl2-net-dev
```

# Controls

| Button          | Action                                                                                       |
|-----------------|----------------------------------------------------------------------------------------------|
| Left-Click      | Select a player                                                                              |
| Right-Click     | Shoot (when player is selected) at cursor location. Hold down to charge for a faster bullet. |
| Space           | Jump (when player is selected) towards cursor location. Hold down to charge for faster jump. |
| C               | Select character and center                                                                  |
| T               | Select character, center, and track                                                          |
| Ctrl-Left-Click | Rotate view around center                                                                    |
| Scroll Down     | Zoom view out                                                                                |
| Scroll Up       | Zoom view in towards cursor                                                                  |
| Q               | Quit game                                                                                    |
| K               | Freeze character                                                                             |
| Shift-K          | Unfreeze character                                                                           |

# Server/Client

To start a server or play locally, just run the `battleroom` binary. You can edit the port in the `startup.yml` in then `res` directory to look something like this. 

```
WorldUpdater: Server
    Port: <port of host>
    User: <your username>
```

To connect to a server, either edit your `startup.yml` to look below or edit `client.yml` and run `battleroom client`.

```
WorldUpdater: Client
    Host: <ip of host>
    Port: <port of host>
    User: <your username>
```

