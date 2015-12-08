#!/bin/bash

mkdir -p /tmp/Jupiter-tmp
wget http://dl.google.com/android/ndk/android-ndk-r10e-linux-x86_64.bin -P /tmp/Jupiter-tmp

chmod +x /tmp/Jupiter-tmp/android-ndk-r10e-linux-x86_64.bin

if [[ "$#" -ge 2 ]]; then
	/tmp/Jupiter-tmp/android-ndk-r10e-linux-x86_64.bin x -o$(readlink -f $2)
else;
	/tmp/Jupiter-tmp/android-ndk-r10e-linux-x86_64.bin x -o$(zenity --file-selection --directory)
fi

rm -rf /tmp/Jupiter-tmp/
