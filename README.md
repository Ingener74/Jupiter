#Jupiter small game engine

##How to build on Linux

###1. install dependencies

1.1. install other dependencies

```
sudo apt-get install libegl1-mesa-dev libglew1.10 libglew-dev freeglut3 freeglut3-dev libglm-dev libxmu6 libxmu-dev swig2.0 swig2.0-doc swig2.0-examples
```

1.2. libpng 

download libpng-<version>.tar.gz

```
cd libpng
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```

1.3. Box2D

download last version of Box2D

```
7z x Box2D
cd Box2D/Box2D
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
cmake ..
make
```
