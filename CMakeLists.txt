cmake_minimum_required(VERSION 3.0.2)
project(gravity)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

# No optimization, gdb-friendly, warnings
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_EXPORT_COMPILECOMMANDS ON)

message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
message("Compiler flags: ${CMAKE_CXX_FLAGS}")
message("Compiler: ${CMAKE_C_COMPILER}")


# Boost
find_package(Boost COMPONENTS 
    system 
    filesystem 
    # program_options
    # date_time
    REQUIRED
)
FIND_PACKAGE(OpenGL)
find_package(Irrlicht REQUIRED)

FIND_LIBRARY(COCOA_LIBRARY Cocoa)
FIND_LIBRARY(IOKIT_LIBRARY IOKit)
SET(OSX_LIBRARIES ${COCOA_LIBRARY} ${IOKIT_LIBRARY})


set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

# Directories
set(src "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(bin "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(lib "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(inc "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(res "${CMAKE_CURRENT_SOURCE_DIR}/assets")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${lib})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${lib})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin})

add_subdirectory(${src})


################################################################################
#                                   Testing                                    #
################################################################################
set(GTEST_DIR $ENV{GTEST_DIR})
set(testdir "${CMAKE_CURRENT_SOURCE_DIR}/test")
add_subdirectory(${testdir})
message("Using google test: ${GTEST_DIR}")
include_directories(
  "${GTEST_DIR}/include"
)
link_directories(
  "${GTEST_DIR}"
)
enable_testing()
add_test(NAME suite COMMAND test_suite)

