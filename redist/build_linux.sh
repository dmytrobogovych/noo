##!/usr/bin/sh

# Make build or upload existing
MAKE_BUILD=YES

# Prepare publishing
PREPARE_PUBLISH=YES

# Upload build or no
PUBLISH_BUILD=YES

# Codesign id
SIGNID="Developer ID Application: Dmytro Bogovych (563QRB9S29)"

# Default values only - no need to change every run
ZIPBUILD=Litt-osx-0.9.2.dmg
DMGBUILD=Litt-osx-0.9.2.dmg

# Find version
cd ../client
version=`less chooka.pro | grep "VERSION =" | cut -d' ' -f 3`

echo "Found version: $version"

if [ "$MAKE_BUILD" = "YES" ]; then
	# qmake
	echo Remove old build
	rm -rf build
        mkdir build

	echo Running cmake
	QT_BINARY_DIR=/Users/anand/qt/5.12.2/clang_64/bin
	cd build
	QT_CMAKE_DIR=~/qt/5.12.2/clang_64/lib/cmake
	cmake .. -D Qt5Core_DIR=$QT_CMAKE_DIR/Qt5Core                   \
	         -D Qt5Widgets_DIR=$QT_CMAKE_DIR/Qt5Widgets             \
	         -D Qt5PrintSupport_DIR=$QT_CMAKE_DIR/Qt5PrintSupport   \
	         -D Qt5Network_DIR=$QT_CMAKE_DIR/Qt5Network             \
	         -D Qt5OpenGL_DIR=$QT_CMAKE_DIR/Qt5OpenGL               \
	         -D Qt5LinguistTools_DIR=$QT_CMAKE_DIR/Qt5LinguistTools

        if [ $? -ne 0 ]; then
            echo "cmake failed. Exiting."
            exit
        fi

	cmake --build . -j4
        if [ $? -ne 0 ]; then
            echo "cmake build failed. Exiting."
            exit
        fi
        

	echo Deploying Qt libraries
	$QT_BINARY_DIR/macdeployqt Litt.app -codesign="$SIGNID"
        if [ $? -ne 0 ]; then
            echo "macdeployqt failed. Exiting."
            exit
        fi
        echo "Codesign is skipped for now, please purchase a Apple developer subscription!"
	#codesign -s $CODESIGN Litt.app 

	# mkdir Chooka.app/Contents/Resources

	# echo Cleaning object files
	#rm -rf *.o
	 # rm -rf Makefile

	zip -r ../../Litt.zip Litt.app
	
	# Rename zip file
	mv ../../Litt.zip ../../Litt-osx-$version.zip
	ZIPBUILD=Litt-osx-$version.zip

	echo Prepare DMG file
	cd ../../
	dmgbuild -s redist/dmgsettings.py "Litt application" Litt-osx-$version.dmg
	DMGBUILD=Litt-osx-$version.dmg
fi


if [ "$PREPARE_PUBLISH" = "YES" ]; then
	# Updating release notes file & application cast file
	redist/updater.py -v $version -d $DMGBUILD -r site/releasenotes.html -c redist/changes.html -a site/LittAppCast.xml

	# Format cast file
	xmllint -format site/LittAppCast.xml > site/LittAppCast2.xml
	rm -rf site/LittAppCast.xml
	mv site/LittAppCast2.xml site/LittAppCast.xml

	# Prepare index.html
#	sed -i "s/Litt-osx.*\\.zip/$ZIPBUILD/g" ../site/index.html
# .bak modifier will produce backup file for index.html; it is neccessary for OS X
	sed -i.bak "s/Litt-osx.*\\.dmg/$DMGBUILD/g" site/index.html
fi

UPLOAD_ROLE=root@voipobjects.com
if [ "$PUBLISH_BUILD" = "YES" ]; then
	# Copy to server
	echo Copying files...
	scp $DMGBUILD $UPLOAD_ROLE:/var/www/satorilight.com/public_html/downloads
	scp $ZIPBUILD $UPLOAD_ROLE:/var/www/satorilight.com/public_html/downloads
	scp site/releasenotes.html $UPLOAD_ROLE:/var/www/satorilight.com/public_html
	scp site/LittAppCast.xml $UPLOAD_ROLE:/var/www/satorilight.com/public_html
	scp site/index.html $UPLOAD_ROLE:/var/www/satorilight.com/public_html

	echo Modify symbol links...
#	ssh uploader@voipobjects.com ln -s /var/www/satorilight.com/public_html/downloads/$ZIPBUILD /var/www/satorilight.com/public_html/downloads/litt-osx.zip
	ssh $UPLOAD_ROLE rm /var/www/satorilight.com/public_html/downloads/litt-osx.dmg
	ssh $UPLOAD_ROLE ln -s /var/www/satorilight.com/public_html/downloads/$DMGBUILD /var/www/satorilight.com/public_html/downloads/litt-osx.dmg
	ssh $UPLOAD_ROLE rm /var/www/satorilight.com/public_html/downloads/Litt-osx.dmg
	ssh $UPLOAD_ROLE ln -s /var/www/satorilight.com/public_html/downloads/$DMGBUILD /var/www/satorilight.com/public_html/downloads/Litt-osx.dmg
fi


