#-------------------------------------------------
#
# Project created by QtCreator 2014-01-21T12:27:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
CONFIG += c++11
TARGET = Litt
TEMPLATE = app
VERSION = 0.9.1
VERSTR = '\\"$${VERSION}\\"'
DEFINES += VER=\"$${VERSTR}\"

win32 {
    DEFINES += TARGET_WIN
}

macx {
    QMAKE_MAC_SDK = macosx10.14
    DEFINES += TARGET_OSX
    # DEFINES += USE_LOGGER
    LIBS += ../lib/osx/libssl.a ../lib/osx/libcrypto.a
    LIBS += -framework CoreFoundation
    LIBS += -framework Cocoa
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -std=c++0x
    QMAKE_LFLAGS +=  -std=c++11

    License.files = License.rtf
    License.path = Contents/Resources
    QMAKE_BUNDLE_DATA += License
}

ICON = icons/appicon-osx.icns

DEFINES += USE_ENCRYPTED_DB
DEFINES += SQLITE_HAS_CODEC SQLITE_TEMP_STORE=2 SQLITE_THREADSAFE
INCLUDEPATH += sqlitecpp/include
INCLUDEPATH += ../lib/include


SOURCES += main.cpp\
    mainwindow.cpp \
    storage.cpp \
    task.cpp \
    tasktreemodel.cpp \
    helper.cpp \
    encryption.cpp \
    newpassworddlg.cpp \
    passworddlg.cpp \
    appevents.cpp \
    sqlitecpp/src/Column.cpp \
    sqlitecpp/src/Database.cpp \
    sqlitecpp/src/Statement.cpp \
    sqlitecpp/src/Transaction.cpp \
    sqlite3.c \
    preferencesdlg.cpp \
    settings.cpp \
    timetreedlg.cpp \
    timetreemodel.cpp \
    timereportwizard.cpp \
    platforms/hidtracker.cpp \
    platforms/hidtrackerimpl.cpp \
    logger.cpp \
    timeintervaldlg.cpp \
    aboutdlg.cpp \
    attachmentslist.cpp \
    attachmentsdialog.cpp \
    taskaction.cpp \
    finddialog.cpp \
    findsupport.cpp \
    stopworkdialog.cpp \
    startworkdialog.cpp \
    twofish.cpp \
    openorcreatedb_widget.cpp \
    connectdb_widget.cpp

HEADERS  += mainwindow.h \
    storage.h \
    task.h \
    tasktreemodel.h \
    config.h \
    helper.h \
    encryption.h \
    appevents.h \
    newpassworddlg.h \
    passworddlg.h \
    appevents.h \
    sqlitecpp/include/SQLiteCpp/Assertion.h \
    sqlitecpp/include/SQLiteCpp/Column.h \
    sqlitecpp/include/SQLiteCpp/Database.h \
    sqlitecpp/include/SQLiteCpp/Exception.h \
    sqlitecpp/include/SQLiteCpp/SQLiteCpp.h \
    sqlitecpp/include/SQLiteCpp/Statement.h \
    sqlitecpp/include/SQLiteCpp/Transaction.h \
    preferencesdlg.h \
    settings.h \
    timetreedlg.h \
    timetreemodel.h \
    timereportwizard.h \
    sqlite3.h \
    sqlite3ext.h \
    platforms/hidtracker.h \
    platforms/hidtrackerimpl.h \
    platforms/osx/hidtrackerimpl_osx.h \
    logger.h \
    timeintervaldlg.h \
    aboutdlg.h \
    attachmentslist.h \
    attachmentsdialog.h \
    platforms/osx/sleeptracker_osx.h \
    taskaction.h \
    finddialog.h \
    findsupport.h \
    stopworkdialog.h \
    startworkdialog.h \
    twofish.h \
    openorcreatedb_widget.h \
    connectdb_widget.h

FORMS    += mainwindow.ui \
    newpassworddlg.ui \
    passworddlg.ui \
    preferencesdlg.ui \
    timetreedlg.ui \
    timeintervaldlg.ui \
    aboutdlg.ui \
    attachmentslist.ui \
    attachmentsdialog.ui \
    finddialog.ui \
    stopworkdialog.ui \
    startworkdialog.ui \
    openorcreatedb_widget.ui \
    connectdb_widget.ui

RESOURCES = mainwindow.qrc resources/qdarkstyle/style.qrc

OBJECTIVE_SOURCES += \
    platforms/osx/hidtrackerimpl_osx.mm \
    platforms/osx/sleeptracker_osx.mm

!include("fervor/Fervor.pri") {
	error("Unable to include Fervor autoupdater.")
}

!include("qtkeychain/qt5keychain.pri") {
        error("Unable to include QTKeyChain library.")
}
