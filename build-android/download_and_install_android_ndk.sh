#!/bin/bash

# TODO 
# Сделать проверку переменных состояния ANDROID_NDK и ANDROID_STANDALONE_TOOLCHAIN

mkdir -p /tmp/Jupiter-tmp

wget http://dl.google.com/android/ndk/android-ndk-r10e-linux-x86_64.bin -P /tmp/Jupiter-tmp

chmod +x /tmp/Jupiter-tmp/android-ndk-r10e-linux-x86_64.bin

if [ "$#" -ge 1 ]; then
	/tmp/Jupiter-tmp/android-ndk-r10e-linux-x86_64.bin x -o$(readlink -f $1)
else
	/tmp/Jupiter-tmp/android-ndk-r10e-linux-x86_64.bin x -o$(zenity --file-selection --directory)
fi

rm -rf /tmp/Jupiter-tmp/
