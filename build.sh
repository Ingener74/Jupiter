#!/bin/bash

install_deps=`zenity --question --title="Install dependencies?" --text="Do you really install dependencies?" --timeout=7`
if [ $? -eq "0" ]; then
	echo "Yes"
else
	echo "No"
fi

cmake_dir=`zenity --file-selection --directory --title="Select directory <Qt5 directory>/5.4/gcc_64/lib/cmake"`
build_type=`zenity --list --radiolist --title="Select build type" --text="Select build type" --column="" --column="Build type" TRUE Debug FALSE Release`

mkdir -p build && cd build && cmake .. -DCMAKE_PREFIX_PATH=$cmake_dir -DCMAKE_BUILD_TYPE=$build_type && make
