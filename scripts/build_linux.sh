#!/bin/bash

# I use this script on two different hosts so there are logic to find proper Qt installation

export QT_HOME=/home/$USER/qt5.15/5.15.2/gcc_64
if [ ! -d "$QT_HOME" ] ; then
	export QT_HOME=/home/$USER/qt5.15/5.15.2/gcc_64
fi

# Build .appimage
/usr/bin/python3 build_outliner.py

