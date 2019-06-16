<img src="https://svgshare.com/i/Ayv.svg" width="100" height="100" alt="image description"></image>  
# Scarecrow2D
[![Build Status](https://travis-ci.org/NovaSurfer/scarecrow2d.svg?branch=master)](https://travis-ci.org/NovaSurfer/scarecrow2d)

# Compiling
## Getting the sourse code
`git clone --recursive https://github.com/NovaSurfer/2D-Game.git`  
(using recursive cloning we are able to clone all of the dependencies in a proper way)

## Environment requirenments
### Linux:
- gcc-7
- g++-7
- libevent-dev
- doxygen
- xorg-dev
- libglu1-mesa-dev
### Windows:
- MinGW-w64

## Building
```console
$ mkdir build
$ cd build/
```
### Linux:
```console
$ cmake ../
$ make
$ make test
```
### Windows:
```console
$ cmake ../ -DCMAKE_SH="CMAKE_SH-NOT_FOUND" -DCMAKE_BUILD_TYPE="Debug" -G "MinGW Makefiles"
$ mingw32-make.exe
$ ./2d_game.exe
$ ./game_test.exe
