#!/bin/bash

sudo apt-get install libegl1-mesa-dev libxmu6 libxmu-dev zlib1g-dev libpython-dev libpcre3-dev p7zip-full libxi-dev libreadline-dev xorg-dev

cd /tmp/
wget http://downloads.sourceforge.net/project/swig/swig/swig-3.0.7/swig-3.0.7.tar.gz
tar xf swig-3.0.7.tar.gz 
cd swig-3.0.7/
./configure 
make -j4
sudo make install

