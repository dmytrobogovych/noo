cmake_minimum_required(VERSION 2.8.3)
project(Fervor)

option (FERVOR_BUILD_SAMPLE "Should the sample be built?" OFF)
option (FERVOR_BUILD_TESTS "Should the tests be built" OFF)

find_package (Qt5Core REQUIRED)
find_package (Qt5Gui REQUIRED)
find_package (Qt5Network REQUIRED)

set (QT_USE_QTNETWORK true)
set (QT_USE_QTWEBKIT true)

set (FERVOR_APP_VERSION "${APP_VERSION}")
set (FERVOR_APP_NAME "Litt")

# Instruct CMake to run moc automatically when needed.
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run uic automatically when needed.
set (CMAKE_AUTOUIC ON)


#include(${QT_USE_FILE})
#add_definitions(${QT_DEFINITIONS})
if(DEFINED FERVOR_APP_VERSION)
    add_definitions(-DFV_APP_VERSION="${FERVOR_APP_VERSION}")
else()
    add_definitions(-DFV_APP_VERSION="1.0")
    message(WARNING "No version information for Fervor given (please set FERVOR_APP_VERSION)! Assuming 1.0.")
endif()

if(DEFINED FERVOR_APP_NAME)
    add_definitions(-DFV_APP_NAME="${FERVOR_APP_NAME}")
else()
    add_definitions(-DFV_APP_NAME="App Name")
    message(WARNING "No application name for Fervor given (please set FERVOR_APP_NAME)! Assuming 'App Name'.")
endif()

set(SOURCES
    fvavailableupdate.cpp
    fvignoredversions.cpp
    fvplatform.cpp
    fvupdateconfirmdialog.cpp
    fvupdater.cpp
    fvupdatewindow.cpp
    fvversioncomparator.cpp
    )

set(MOC_HEADERS
    fvavailableupdate.h
    fvignoredversions.h
    fvplatform.h
    fvupdateconfirmdialog.h
    fvupdater.h
    fvupdatewindow.h
    )

set(UIS
    fvupdateconfirmdialog.ui
    fvupdatewindow.ui
    )

#qt4_wrap_ui(UI_HEADERS ${UIS})
#qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )
include_directories (${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})

add_library(Fervor ${SOURCES} ${MOC_HEADERS} ${MOC_SOURCES} ${UIS})

if(FERVOR_BUILD_SAMPLE)
    add_subdirectory(sample)
endif()
if(FERVOR_BUILD_TESTS)
    ENABLE_TESTING()
    add_subdirectory(tests)
endif()
