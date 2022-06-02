APPICON=appicon-osx.png
ICONSET=appicon-osx.iconset
mkdir $ICONSET
sips -z 16 16     $APPICON --out $ICONSET/icon_16x16.png
sips -z 32 32     $APPICON --out $ICONSET/icon_16x16@2x.png
sips -z 32 32     $APPICON --out $ICONSET/icon_32x32.png
sips -z 64 64     $APPICON --out $ICONSET/icon_32x32@2x.png
sips -z 128 128   $APPICON --out $ICONSET/icon_128x128.png
sips -z 256 256   $APPICON --out $ICONSET/icon_128x128@2x.png
sips -z 256 256   $APPICON --out $ICONSET/icon_256x256.png
sips -z 512 512   $APPICON --out $ICONSET/icon_256x256@2x.png
sips -z 512 512   $APPICON --out $ICONSET/icon_512x512.png
cp $APPICON $ICONSET/icon_512x512@2x.png
iconutil -c icns appicon-osx.iconset
# rm -R $ICONSET
