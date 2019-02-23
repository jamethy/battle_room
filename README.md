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
cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-net-dev
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
| Shift-K         | Unfreeze character                                                                           |

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


# Code Sections
I'm just going to describe the various sections of the codebase here. Its pretty incomplete/messy right now.

## animation
An animation in Battle Room describes what to display for an in-game object and how it is shaped. The general structure of an animation is ...

## application
## common
## display_window
## world

### Copies of the world
A game world (`World`) is an instance in time in the game containing all the objects currently in play. Currently this includes the game objects, background objects, and the current game time in seconds. It can be copied around and serialized. Just a container for the game world, does not do any updating.

The `QueryWorld` Is a singleton layer on top of static copies of the world that can be queried with thread safety.

### Updating World
A `LocalUpdatingWorld` is a child class of `World` that can update. This is where all the game update logic is.

The `QueryWorld` is updated through various implementations of the `QueryWorldUpdater` class. They all contains ways to communicate commands to the server, register and unregister users. The simplest version of this is the `LocalWorldUpdater` - it just contains a `LocalUpdatingWorld` and runs updates on another thread. A layer on top of that is `ServerConnection` which just serves the local updating world to the network. The last updater is the `ClientConnection` which connets to a server and receives updates from it and in turn updates the query world. 

So, in summary:
* Playing Locally: Use `LocalWorldUpdater` which contains `LocalUpdatingWorld` and updates `QueryWorld` with it.
* As a server: Use `ServerConnection` which extends `LocalWorldUpdater` and also reads from `QueryWorld` to serve to the network.
* As a client: Use `ClientConnection` which asks the server for the world and updates `QueryWorld` based on its response.

## networking
## views
