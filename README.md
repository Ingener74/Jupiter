##Jupiter small game engine

### How include in Android (NativeActivity/JNI) Project

### How to build on Linux

install dependencies

1. Install Qt5 from http://qt-project.org/downloads

2. Install other dependencies
```
sudo apt-get install libegl1-mesa-dev libglew1.10 libglew-dev freeglut3 freeglut3-dev libglm-dev libxmu6 libxmu-dev
```
3. Build and install dependencies

libpng
3.1 Download libpng-<version>.tar.gz
```
cd libpng
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```
4. Build
```
git clone https://github.com/Ingener74/Jupiter.git
cd Jupiter
mkdir build
cmake -DCMAKE_PREFIX_PATH=~/Qt5.3.1/5.3/gcc_64/lib/cmake ..
make
```