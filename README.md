##Jupiter small game engine

### How include in Android (NativeActivity/JNI) Project

### How to build on Linux

install dependencies

1. Install Qt5 from http://qt-project.org/downloads

2. Install 
```
sudo apt-get install libegl1-mesa-dev libglew1.10 libglew-dev
```

3. Make directory Jupiter/build

4. Go to Jupiter/build

5. Make 

```
cmake .. -DCMAKE_PREFIX_PATH=~/Qt5.3.1/5.3/gcc_64/lib/cmake
```

6. Do make

```
make
```