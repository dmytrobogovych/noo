##!/usr/bin/sh

# qmake
echo Remove old build

cd ../client
rm -rf Litt.app
rm -rf *.o
rm -rf Makefile

echo Running qmake                        

QT_BINARY_DIR=/usr/bin
#QT_BINARY_DIR=/Users/anand/Qt-5.3-mac/5.3/clang_64/bin
$QT_BINARY_DIR/qmake -spec macx-g++ chooka.pro

echo Building
make clean
make

echo Deploying Qt libraries
$QT_BINARY_DIR/macdeployqt Litt.app

mkdir Chooka.app/Contents/Resources

echo Cleaning object files
rm -rf *.o
rm -rf Makefile

zip -r ../Litt.zip Litt.app

# Rename zip file
version=`less chooka.pro | grep "VERSION =" | cut -d' ' -f 3`
mv ../Litt.zip ../Litt-osx-$version.zip

# Copy to server
echo Please put your uploader password
scp ../Litt-osx-$version.zip uploader@voipobjects.com:/home/uploader/
