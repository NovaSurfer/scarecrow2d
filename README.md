<img src="https://svgshare.com/i/Ayv.svg" width="100" height="100" alt="image description"></image>  
# Scarecrow2D  

![Linux - GCC](https://github.com/NovaSurfer/scarecrow2d/workflows/Linux%20-%20GCC/badge.svg)  ![Windows - MSVC](https://github.com/NovaSurfer/scarecrow2d/workflows/Windows%20-%20MSVC/badge.svg)  ![macOS - Clang](https://github.com/NovaSurfer/scarecrow2d/workflows/macOS%20-%20Clang/badge.svg)   
2D game / sandbox project made using C++ and OpenGL

## Getting the sourse code
`git clone --recursive https://github.com/NovaSurfer/scarecrow2d.git`  
(using recursive cloning we are able to clone all of the dependencies in a proper way)

## Pre-requirements
##### Linux
- gcc-7
- g++-7
- libevent-dev
- doxygen
- xorg-dev
- libglu1-mesa-dev
```console
$ sudo apt-get install libevent-dev xorg-dev libglu1-mesa-dev 
```
##### MacOS
```console
$ brew install libevent 
```

##### Windows
- MSVC or MinGW-w64

###### Documentation building pre-requirements (if needed)
Doxygen, Sphinx, Breathe
```console
$ pip3 install -U sphinx && pip3 install sphinx_rtd_theme && pip3 install breathe
```
[Doxygen installer](https://www.doxygen.nl/download.html) (for Windows)  
Linux / MacOS: ```sudo apt-get install doxygen / brew install doxygen```


## Building
```console
$ mkdir build && cd build
```
### Linux / MacOS:
```console
$ cmake ../ -DCMAKE_BUILD_TYPE=Debug -DSC2D_BUILD_TESTS=ON
$ cmake --build . --config Debug
$ ./game_test
$ ./scarecrow2d
```
### Windows:
```console
$ cmake -DSC2D_BUILD_TESTS=ON -G "Visual Studio 16 2019" ../
$ devenv scarecrow2d.sln /build Debug
$ game_test.exe
$ scarecrow2d.exe
```
