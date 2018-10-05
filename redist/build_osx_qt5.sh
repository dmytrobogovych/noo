##!/usr/bin/sh

# Make build or upload existing
MAKEBUILD=YES

# Prepare publishing
PREPAREPUBLISH=YES

# Upload build or no
PUBLISHBUILD=YES

# Codesign id
SIGNID="Developer ID Application: Dmytro Bogovych (563QRB9S29)"

# Default values only - no need to change every run
ZIPBUILD=Litt-osx-0.9.0.dmg
DMGBUILD=Litt-osx-0.9.0.dmg
cd ../client
version=`less chooka.pro | grep "VERSION =" | cut -d' ' -f 3`

if [ "$MAKEBUILD" = "YES" ]; then
	# qmake
	echo Remove old build
	rm -rf Litt.app
	rm -rf *.o
	rm -rf Makefile

	echo Running qmake                        
	QT_BINARY_DIR=/Users/anand/Qt/5.9.5/clang_64/bin
	$QT_BINARY_DIR/qmake chooka.pro

	echo Building
	make clean
	make

	echo Deploying Qt libraries
	$QT_BINARY_DIR/macdeployqt Litt.app -codesign="$SIGNID"
	#codesign -s $CODESIGN Litt.app 

	mkdir Chooka.app/Contents/Resources

	echo Cleaning object files
	rm -rf *.o
	rm -rf Makefile

	zip -r ../Litt.zip Litt.app
	
	# Rename zip file
	mv ../Litt.zip ../Litt-osx-$version.zip
	ZIPBUILD=Litt-osx-$version.zip

	echo Prepare DMG file
	cd ../redist
	dmgbuild -s dmgsettings.py "Litt application" ../Litt-osx-$version.dmg
	DMGBUILD=Litt-osx-$version.dmg
fi

cd ../client

if [ "$PREPAREPUBLISH" = "YES" ]; then
	# Updating release notes file & application cast file
	../redist/updater.py -v $version -d ../$DMGBUILD -r ../site/releasenotes.html -c ../redist/changes.html -a ../site/LittAppCast.xml

	# Format cast file
	xmllint -format ../site/LittAppCast.xml > ../site/LittAppCast2.xml
	rm -rf ../site/LittAppCast.xml
	mv ../site/LittAppCast2.xml ../site/LittAppCast.xml

	# Prepare index.html
#	sed -i "s/Litt-osx.*\\.zip/$ZIPBUILD/g" ../site/index.html
# .bak modifier will produce backup file for index.html; it is neccessary for OS X
	sed -i.bak "s/Litt-osx.*\\.dmg/$DMGBUILD/g" ../site/index.html
fi

UPLOAD_ROLE=root@voipobjects.com
if [ "$PUBLISHBUILD" = "YES" ]; then
	# Copy to server
	echo Copying files...
	scp ../$DMGBUILD $UPLOAD_ROLE:/var/www/satorilight.com/public_html/downloads
#	scp ../$ZIPBUILD uploader@voipobjects.com:/var/www/satorilight.com/public_html/downloads
	scp ../site/releasenotes.html $UPLOAD_ROLE:/var/www/satorilight.com/public_html
	scp ../site/LittAppCast.xml $UPLOAD_ROLE:/var/www/satorilight.com/public_html
	scp ../site/index.html $UPLOAD_ROLE:/var/www/satorilight.com/public_html

	echo Modify symbol links...
#	ssh uploader@voipobjects.com ln -s /var/www/satorilight.com/public_html/downloads/$ZIPBUILD /var/www/satorilight.com/public_html/downloads/litt-osx.zip
	ssh $UPLOAD_ROLE rm /var/www/satorilight.com/public_html/downloads/litt-osx.dmg
	ssh $UPLOAD_ROLE ln -s /var/www/satorilight.com/public_html/downloads/$DMGBUILD /var/www/satorilight.com/public_html/downloads/litt-osx.dmg
	ssh $UPLOAD_ROLE rm /var/www/satorilight.com/public_html/downloads/Litt-osx.dmg
	ssh $UPLOAD_ROLE ln -s /var/www/satorilight.com/public_html/downloads/$DMGBUILD /var/www/satorilight.com/public_html/downloads/Litt-osx.dmg
fi


