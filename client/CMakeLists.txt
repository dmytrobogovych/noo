cmake_minimum_required(VERSION 3.5)

# This directive is ignored for non OSX environments
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE STRING "Minimum OS X deployment version")

project (outliner C CXX) # Your project name

if (NOT LIB_PLATFORM)
    message(FATAL_ERROR "No LIB_PLATFORM is set.")
endif()

include (${LIB_PLATFORM}/platform_libs.cmake)

# C++ 11 standard
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Find includes in corresponding build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run uic automatically when needed.
set (CMAKE_AUTOUIC ON)

set (APP_SKIP_BUILD_NUMBER OFF CACHE BOOL "Skip Sevana HASQ build number increase.")

# Use pvqa2 library also
set (USE_PVQA2_LIBRARY OFF CACHE BOOL "Integrate PVQA2.")

# Avoid increasing PVQA/AQuA library build numbers
set (SKIP_BUILD_NUMBER ON)

# Special build for audiologists
set (AUDIOLOGY_EDITION OFF CACHE BOOL "Make special build for audiologists")

# Special build with live capture
set (LIVE_PVQA_EDITION OFF CACHE BOOL "Make special build with live capture")

# This will find the Qt5 files. You will need a QT5_DIR env variable
find_package (Qt5Core REQUIRED)
find_package (Qt5Widgets REQUIRED) # Equivalent of QT += widgets
find_package (Qt5PrintSupport REQUIRED)
find_package (Qt5OpenGL REQUIRED)

if (Qt5OpenGL_FOUND)
    message("Qt5 OpenGL found")
else (Qt5OpenGL_FOUND)
    message("Qt5 OpenGL not found")
endif(Qt5OpenGL_FOUND)

# List all source files in project directory
file (GLOB SOURCES      "*.cpp")
file (GLOB C_SOURCES    "*.c")
file (GLOB HEADERS      "*.h")
file (GLOB UI           "*.ui")

if (CMAKE_SYSTEM MATCHES "Windows*")
    add_definitions(-DTARGET_WIN)
    set (TARGET_WIN ON)
endif()

if (CMAKE_SYSTEM MATCHES "Darwin*")
    add_definitions(-DTARGET_OSX)
    set (TARGET_OSX ON)
endif()

if (CMAKE_SYSTEM MATCHES "Linux*")
    add_definitions (-DTARGET_LINUX)
    set (TARGET_LINUX ON)
endif()

# sevana pvqa
if (TARGET_LINUX)
    set (PLATFORM_LIBS pthread m z dl)
    set (SCRIPT_PROCESSOR "/bin/bash")
    set (BUILD_NUMBER_SCRIPT build_number.sh)
endif()

if(TARGET_OSX)
    # OS X Specific flags
    add_definitions(-DTARGET_OSX)

    set (SCRIPT_PROCESSOR "/bin/bash")
    set (BUILD_NUMBER_SCRIPT build_number.sh)
    set (ADDITIONAL_EXE_OPTIONS MACOSX_BUNDLE)

    set (MACOS_ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../icons/sound_ruler.icns)
endif()

if (TARGET_WIN)
    # Windows Specific flags - MSVC expected
    add_definitions(
	-D_CRT_SECURE_NO_WARNINGS -DHAVE_WINSOCK2_H
	-D_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS -DUNICODE -D_UNICODE )
    set (PLATFORM_LIBS Qt5::WinMain Ws2_32 crashrpt)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
    link_directories(
              ${CMAKE_CURRENT_SOURCE_DIR}/../libs/crashrpt/lib/dll
              )
    set (SCRIPT_PROCESSOR "Powershell.exe" )
    set (BUILD_NUMBER_SCRIPT build_number.ps1)

    # Application icon
    set (WINDOWS_RESOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/icon_soundruler.rc)
    #qt5_add_resources(UI_RESOURCES ${WINDOWS_RESOURCE_PATH})
endif()

# List resources
qt5_add_resources(UI_RESOURCES resources/qdarkstyle/style.qrc)

# Global defines
add_definitions(-DQTKEYCHAIN_NO_EXPORT -DSQLITE_HAS_CODEC -DSQLITE_OMIT_LOAD_EXTENSION)

# Add sqlitecpp & qtkeychain
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sqlitecpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/qtkeychain)
if (TARGET_OSX)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fervor)
endif()

# This will create you executable
set (EXE_NAME litt_outliner)

add_executable(${EXE_NAME}
    ${ADDITIONAL_EXE_OPTIONS}
    ${SOURCES} ${C_SOURCES} ${HEADERS} ${UI}
    ${CMAKE_CURRENT_SOURCE_DIR}/qmarkdowntextedit/qmarkdowntextedit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qmarkdowntextedit/markdownhighlighter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qmarkdowntextedit/qplaintexteditsearchwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platforms/hidtracker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platforms/hidtrackerimpl.cpp
    ${UI_RESOURCES}
    ${MACOS_ICON_FILE}
    ${RESOURCE_FILES}
    ${WINDOWS_RESOURCE_PATH})

target_include_directories(${EXE_NAME} SYSTEM BEFORE
    #PUBLIC ${UUID_INCLUDE}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sqlitecpp/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sqlitecpp/sqlite3/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lib/openssl/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lib/uuid/include
    )


if (TARGET_OSX)
    set_source_files_properties( ${MACOS_ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
    set_target_properties( ${EXE_NAME} PROPERTIES   MACOSX_BUNDLE_ICON_FILE ${MACOS_ICON_FILE} )
    set_target_properties( ${EXE_NAME} PROPERTIES   OUTPUT_NAME ${PRODUCT_NAME})
    set_target_properties( ${EXE_NAME} PROPERTIES   MACOSX_BUNDLE_BUNDLE_NAME ${PRODUCT_NAME} )
    set_target_properties( ${EXE_NAME} PROPERTIES   MACOSX_BUNDLE_SHORT_VERSION_STRING "0.7.8")
    set_target_properties( ${EXE_NAME} PROPERTIES   MACOSX_BUNDLE_LONG_VERSION_STRING "0.7.8")

    set_target_properties( ${EXE_NAME} PROPERTIES   MACOSX_BUNDLE TRUE
                                                    MACOSX_BUNDLE_GUI_IDENTIFIER "biz.sevana.hasq"
                                                    RESOURCE "${RESOURCE_FILES}")
endif()

# This will link necessary Qt5 libraries to your project
target_link_libraries(${EXE_NAME}
    SQLiteCpp
    qtkeychain
    #${UUID_LIB}
    uuid
    ${OPENSSL_CRYPTO}
    Qt5::Core Qt5::Widgets Qt5::PrintSupport Qt5::OpenGL                # Qt
    ${PLATFORM_LIBS}                                                    # System specific libraries
    )

if (TARGET_WIN)
    set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
    set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
    set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        # It happens from Qt Creator usually - so use raw output dir
        set (OUTPUT_DIR "${CMAKE_BINARY_DIR}")
    else(CMAKE_BUILD_TYPE MATCHES "Debug")
        # It happens from build script - add configuration name
        set (OUTPUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
    endif(CMAKE_BUILD_TYPE MATCHES "Debug")

    add_custom_command(TARGET ${EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/../libs/crashrpt/lib/dll/crashrpt.dll"
        "${PROJECT_SOURCE_DIR}/../libs/crashrpt/bin/dbghelp.dll"
        "${PROJECT_SOURCE_DIR}/../libs/crashrpt/bin/crashrpt_lang.ini"
        "${PROJECT_SOURCE_DIR}/../libs/crashrpt/bin/CrashSender1403.exe"
        "${OUTPUT_DIR}")
endif()

if (NOT APP_SKIP_BUILD_NUMBER)
    add_custom_command( TARGET ${EXE_NAME}
                        POST_BUILD
                        COMMAND ${SCRIPT_PROCESSOR} ${CMAKE_CURRENT_SOURCE_DIR}/build-number/${BUILD_NUMBER_SCRIPT}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build-number/ )
endif(NOT APP_SKIP_BUILD_NUMBER)
