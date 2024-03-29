# Main CMake file for compiling the library itself, examples and tests.
#
# Copyright (c) 2012-2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT) 

cmake_minimum_required(VERSION 2.6)
project(SQLiteCpp)

option(SQLITE_ENABLE_COLUMN_METADATA "Enable Column::getName(). Require support from sqlite3 library." OFF)
if (SQLITE_ENABLE_COLUMN_METADATA) 
    # Enable the use of SQLite column metadata and Column::getName() method,
    # Require that the sqlite3 library is also compiled with this flag (default under Debian/Ubuntu, but not on Mac OS X).
    add_definitions(-DSQLITE_ENABLE_COLUMN_METADATA)
endif (SQLITE_ENABLE_COLUMN_METADATA)

option(SQLITE_ENABLE_ASSERT_HANDLER "Enable the user defintion of a assertion_failed() handler." OFF)
if (SQLITE_ENABLE_ASSERT_HANDLER) 
    # Enable the user defintion of a assertion_failed() handler (default to false, easier to handler for begginers).
    add_definitions(-DSQLITECPP_ENABLE_ASSERT_HANDLER)
endif (SQLITE_ENABLE_ASSERT_HANDLER)

# Define useful variables to handle OS differences:
if (WIN32)
    set(DEV_NULL                "NUL")
else (WIN32)
    set(DEV_NULL                "/dev/null")
endif (WIN32)
# then Compiler/IDE differences:
if (MSVC)
    set(CPPLINT_ARG_OUTPUT      "--output=vs7")
    set(CPPCHECK_ARG_TEMPLATE   "--template=vs")
    # disable Visual Studio warnings for fopen() used in the example
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Flags for linking with multithread static C++ runtime
    set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} /MT")
    set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else (MSVC)
    set(CPPLINT_ARG_OUTPUT      "--output=eclipse")
    set(CPPCHECK_ARG_TEMPLATE   "--template=gcc")
    if (CMAKE_COMPILER_IS_GNUCXX)
        # GCC flags
        add_definitions(-rdynamic -fstack-protector-all -Wall -Wextra -pedantic -Wformat-security -Winit-self -Wswitch-default -Wswitch-enum -Wfloat-equal -Wshadow -Wcast-qual -Wconversion -Wlogical-op -Winline)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # Clang flags
        add_definitions(-fstack-protector-all -Wall -Wextra -pedantic -Wformat-security -Winit-self -Wswitch-default -Wswitch-enum -Wfloat-equal -Wshadow -Wcast-qual -Wconversion -Winline)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (MSVC)
# and then common variables
set(CPPLINT_ARG_VERBOSE "--verbose=3")
set(CPPLINT_ARG_LINELENGTH "--linelength=120")


## Core source code ##

# adding a new file require explicittly modifing the CMakeLists.txt
# so that CMake knows that it should rebuild the project (it is best practice)

# list of sources files of the library
set(SQLITECPP_SRC
    ${PROJECT_SOURCE_DIR}/src/Column.cpp
    ${PROJECT_SOURCE_DIR}/src/Database.cpp
    ${PROJECT_SOURCE_DIR}/src/Statement.cpp
    ${PROJECT_SOURCE_DIR}/src/Transaction.cpp
    )
source_group(src FILES ${SQLITECPP_SRC})

# list of header files of the library
set(SQLITECPP_INC
    ${PROJECT_SOURCE_DIR}/include/SQLiteCpp/SQLiteCpp.h
    ${PROJECT_SOURCE_DIR}/include/SQLiteCpp/Assertion.h
    ${PROJECT_SOURCE_DIR}/include/SQLiteCpp/Column.h
    ${PROJECT_SOURCE_DIR}/include/SQLiteCpp/Database.h
    ${PROJECT_SOURCE_DIR}/include/SQLiteCpp/Exception.h
    ${PROJECT_SOURCE_DIR}/include/SQLiteCpp/Statement.h
    ${PROJECT_SOURCE_DIR}/include/SQLiteCpp/Transaction.h
    )
source_group(inc FILES ${SQLITECPP_INC})

# list of test files of the library
set(SQLITECPP_TESTS
    tests/Database_test.cpp
    tests/Statement_test.cpp
    )
source_group(tests FILES ${SQLITECPP_TESTS})

# list of example files of the library
set(SQLITECPP_EXAMPLES
    examples/example1/main.cpp
    )
source_group(example1 FILES ${SQLITECPP_EXAMPLES})

# list of doc files of the library
set(SQLITECPP_DOC
    README.md
    WRAPPERS.md
    LICENSE.txt
    TODO.txt
    )
source_group(doc FILES ${SQLITECPP_DOC})

# All includes are relative to the "include" directory 

# add sources of the wrapper as a "SQLiteCpp" static library
add_library(SQLiteCpp ${SQLITECPP_SRC} ${SQLITECPP_INC} ${SQLITECPP_DOC})

target_include_directories(SQLiteCpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3
    ${CMAKE_CURRENT_SOURCE_DIR}/include )

if (UNIX AND (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
    set_target_properties(SQLiteCpp PROPERTIES COMPILE_FLAGS "-fPIC")
endif (UNIX AND (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))

# Optional additional targets:

option(SQLITECPP_RUN_CPPLINT "Run cpplint.py tool for Google C++ StyleGuide." OFF)
if (SQLITECPP_RUN_CPPLINT)
    # add a cpplint target to the "all" target
    add_custom_target(SQLiteCpp_cpplint
        ALL
        COMMAND python ${PROJECT_SOURCE_DIR}/cpplint.py ${CPPLINT_ARG_OUTPUT} ${CPPLINT_ARG_VERBOSE} ${CPPLINT_ARG_LINELENGTH} ${SQLITECPP_SRC} ${SQLITECPP_INC}
        )
else (SQLITECPP_RUN_CPPLINT)
    message(STATUS "SQLITECPP_RUN_CPPLINT OFF")
endif (SQLITECPP_RUN_CPPLINT)

option(SQLITECPP_RUN_CPPCHECK "Run cppcheck C++ static analysis tool." OFF)
if (SQLITECPP_RUN_CPPCHECK)
    find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)
    if (CPPCHECK_EXECUTABLE)
        # add a cppcheck target to the "all" target
        add_custom_target(SQLiteCpp_cppcheck
            ALL
            COMMAND cppcheck -j 4 cppcheck --enable=style --quiet ${CPPCHECK_ARG_TEMPLATE} ${PROJECT_SOURCE_DIR}/src
            )
    else (CPPCHECK_EXECUTABLE)
        message(STATUS "cppcheck not found")
    endif (CPPCHECK_EXECUTABLE)
else (SQLITECPP_RUN_CPPCHECK)
    message(STATUS "SQLITECPP_RUN_CPPCHECK OFF")
endif (SQLITECPP_RUN_CPPCHECK)

option(SQLITECPP_RUN_DOXYGEN "Run Doxygen C++ documentation tool." OFF)
if (SQLITECPP_RUN_DOXYGEN)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # add a Doxygen target to the "all" target
        add_custom_target(SQLiteCpp_doxygen
            ALL
            COMMAND doxygen Doxyfile > ${DEV_NULL}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            )
    else (DOXYGEN_FOUND)
        message(STATUS "Doxygen not found")
    endif (DOXYGEN_FOUND)
else (SQLITECPP_RUN_DOXYGEN)
    message(STATUS "SQLITECPP_RUN_DOXYGEN OFF")
endif (SQLITECPP_RUN_DOXYGEN)

option(SQLITECPP_BUILD_EXAMPLES "Build examples." OFF)
if (SQLITECPP_BUILD_EXAMPLES)
    # add the basic example executable
    add_executable(SQLiteCpp_example1 ${SQLITECPP_EXAMPLES})
    target_link_libraries(SQLiteCpp_example1 SQLiteCpp sqlite3)
else(SQLITECPP_BUILD_EXAMPLES)
    message(STATUS "SQLITECPP_BUILD_EXAMPLES OFF")
endif(SQLITECPP_BUILD_EXAMPLES)

option(SQLITECPP_BUILD_TESTS "Build and run tests." OFF)
if (SQLITECPP_BUILD_TESTS)
    # add the subdirectory containing the CMakeLists.txt for the gtest library
    if (NOT MSVC)
        add_definitions(-Wno-variadic-macros -Wno-long-long -Wno-conversion -Wno-switch-enum)
    endif (NOT MSVC)

    add_subdirectory(googletest)
    include_directories("${PROJECT_SOURCE_DIR}/googletest/include")

    # add the unit test executable
    add_executable(SQLiteCpp_tests ${SQLITECPP_TESTS})
    target_link_libraries(SQLiteCpp_tests gtest_main SQLiteCpp sqlite3)

    # add a "test" target:
    enable_testing()

    # does the tests pass?
    add_test(UnitTests SQLiteCpp_tests)

    if (SQLITECPP_BUILD_EXAMPLES)
        # does the example1 runs successfully?
        add_test(Example1Run SQLiteCpp_example1)
    endif(SQLITECPP_BUILD_EXAMPLES)
else (SQLITECPP_BUILD_TESTS)
    message(STATUS "SQLITECPP_BUILD_TESTS OFF")
endif (SQLITECPP_BUILD_TESTS)
