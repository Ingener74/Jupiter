# Юпитер - игровой движок

![Github Logo](/doc/images/Jupiter.png)

Travis-ci.org
[![Build Status](https://travis-ci.org/Ingener74/Jupiter.svg?branch=master)](https://travis-ci.org/Ingener74/Jupiter)

Drone.io
[![Build Status](https://drone.io/github.com/Ingener74/Jupiter/status.png)](https://drone.io/github.com/Ingener74/Jupiter/latest)

## Сборка под Linux

### 1. установка зависимостей

1.1. install other dependencies

```
sudo apt-get install libegl1-mesa-dev libxmu6 libxmu-dev zlib1g-dev libpython-dev libpcre3-dev p7zip-full libxi-dev libreadline-dev 
```

1.2. SWIG 3
download last version of SWIG 3
```
tar xf swig-<version>.tar.xf
cd <swig-directory>
mkdir build
cd build
cmake ..
make && sudo make install
```

2. build

```
git clone https://github.com/Ingener74/Jupiter.git
cd Jupiter
mkdir build
cmake ..
make
```
