# battle_room
The Battle Room from Ender's Game!

This is a video game I am making for fun that is a 2D action/rts recreation of the battle room from Ender's Game by Orson Scott  Card. I've never made a game before, so here it goes.

### General Code Structure
The code is split up into 7 modules, each creating a library. The interface header files for these libraries are within the interfaces folder. You can see the reaaaally crappy diagram I made to explain it in the documentation folder. So, starting from the bottom:

##### User Interface
This library collects input from input devices (from the graphics library) and interprets them into commands to be sent either to the graphics or player input ( or sound if in menu). Haven't started writing this one yet.

##### Sound
Accepts sound playing requests from game data or the user interface and queues them up to be played.

##### Graphics
Stores/creates objects/menus and their positions to be rendered on screen and accepts animation requests to queue.

##### Player Input
Takes commands from the user interface or the AI and sends commands to the game data to affect the players.

##### AI
Mimics the user interface output to send input to the Player Input library. Also reads from game data to do so.

##### Game Data
This is where all the fun happens. This includes the character info, the physics, the map layouts, everything. And I haven't even started writing it.

##### Networking
I am doing my best to not make this an afterthought. It will communicate what is in Game Data to the outside.

##### Utility
This, while not on the diagram, is involved everywhere. It includes code for things like 2D vectors and the like.

### To Build
Right now I have been just opening the CMakeLists.txt in QtCreator, setting the cmake arguments to '-DCMAKE_BUILD_TYPE=Release', and hitting build. You shouldn't need qtcreator though.

### Other Notes
I have been trying to add a test function for everything in each library. This code is in the testers folder.
