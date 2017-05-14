# battle_room
The Battle Room from Ender's Game!

# Getting Started
To clone the repo use the following:

```shell
git clone --recursive https://github.com/jamethy/battle_room.git
```

If you forgot the recursive, do not worry. Just go to the root of the project and run the following

```shell
git submodule init
git submodule update
```

After this, to build the project create a folder next to _battle\_room_, maybe called _build_ and run the following
```shell
cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../battle_room
make
make test
```

This will make and run all the tests

# Building in Linux
The packages required in Ubuntu include:

```shell
cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-gfx-dev
```
