#Jupiter small game engine

##How to build on Linux

###1. install dependencies

1.1. install Qt5 from http://qt-project.org/downloads

1.2. install other dependencies

```
sudo apt-get install libegl1-mesa-dev libglew1.10 libglew-dev freeglut3 freeglut3-dev libglm-dev libxmu6 libxmu-dev
```

1.3. libpng 

download libpng-<version>.tar.gz

```
cd libpng
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```

2. build

```
git clone https://github.com/Ingener74/Jupiter.git
cd Jupiter
mkdir build
cmake -DCMAKE_PREFIX_PATH=~/Qt5.3.1/5.3/gcc_64/lib/cmake ..
make
```