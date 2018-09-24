APPNAME=Litt
SIGNID="563QRB9S29"

echo --sign app--
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/MacOS/Litt
#exit

echo --sign frameworks--
codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Frameworks/QtCore.framework/Versions/5

#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Frameworks/QtNetwork.framework/Versions/5/QtNetwork
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets

echo --sign plugins--
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Plugins/bearer/libqcorewlanbearer.dylib
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Plugins/bearer/libqgenericbearer.dylib
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Plugins/imageformats/libqgif.dylib
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Plugins/imageformats/libqico.dylib
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Plugins/imageformats/libqjpeg.dylib
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Plugins/platforms/libqcocoa.dylib
#codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app/Contents/Plugins/printsupport/libcocoaprintersupport.dylib

echo --sign app--
codesign --force --verify --verbose --sign "Developer ID Application: $SIGNID" $APPNAME.app

echo --checking signature--
codesign -vvv -d $APPNAME.app





