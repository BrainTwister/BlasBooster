cmake_minimum_required(VERSION 3.0)
project(BlasBooster VERSION 0.2.10 LANGUAGES CXX)
message("${PROJECT_NAME} version ${PROJECT_VERSION}")

# add own cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory)
          and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

# guard against bad build-type strings
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if(    NOT cmake_build_type_tolower STREQUAL "release"
   AND NOT cmake_build_type_tolower STREQUAL "debug"
   AND NOT cmake_build_type_tolower STREQUAL "profiling"
   AND NOT cmake_build_type_tolower STREQUAL "relwithdebinfo")
  message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Release, Debug, Profiling, RelWithDebInfo (case-insensitive).")
endif()

message("CMake build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors -fPIC -fopenmp")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_PROFILING "-O3 -pg")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g -DBLASBOOSTER_DEBUG_MODE")

# C++ ISO standard
set(CPP_ISO_STANDARD "c++14" CACHE STRING "C++ ISO standard")
message("Use ${CPP_ISO_STANDARD} ISO standard")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CPP_ISO_STANDARD}")

if(${CMAKE_CXX_COMPILER} MATCHES "icpc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__GXX_EXPERIMENTAL_CXX0X__ -DNO_INITIALIZER_LIST_SUPPORTED")
endif()

if(${CMAKE_COMPILER_IS_GNUCXX})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=10000 -msse2 -ftrack-macro-expansion=0")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -funroll-loops -ffast-math -mfpmath=sse -march=core2 -mtune=core2 -DBLASBOOSTER_DEBUG_MODE")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops --param max-unroll-times=100 -ffast-math -mfpmath=sse -march=core2 -mtune=core2")
endif()

# Set RPATH relative to executable
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")

set(CMAKE_VERBOSE_MAKEFILE false)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# generate version string
configure_file (
    "${PROJECT_SOURCE_DIR}/include/BlasBooster/Utilities/Version.h.in"
    "${PROJECT_SOURCE_DIR}/include/BlasBooster/Utilities/Version.h"
)

# Boost template libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem serialization system REQUIRED)
if(Boost_FOUND)
    add_definitions(-DUSE_BOOST -DHAVE_SHARED_POINTER -DBOOST_DATE_TIME_POSIX_TIME_STD_CONFIG -DBOOST_SYSTEM_NO_DEPRECATED)
endif(Boost_FOUND)

# Intel math kernel library (MKL)
find_package(MKL)
if(MKL_FOUND)
    add_subdirectory(src/Interfaces/IntelMKL)
endif(MKL_FOUND)

# GotoBLAS/OpenBLAS 
find_package(OpenBLAS)
if(OPENBLAS_FOUND)
    add_subdirectory(src/Interfaces/OpenBLAS)
endif(OPENBLAS_FOUND)

#find_package(Eigen3)
#find_package(MTL4)

add_subdirectory(ArgumentParser)
add_subdirectory(BenchmarkManager)
add_subdirectory(src/Benchmark)
add_subdirectory(src/MatrixFactory)
add_subdirectory(src/Tools)

# Google C++ unit test framework
find_package(GTest)
if(GTEST_FOUND)
    ENABLE_TESTING()
    add_subdirectory(test)
endif(GTEST_FOUND)

# Doxygen API documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)

    set(doxyfile_in ${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in)
    set(doxyfile ${PROJECT_BINARY_DIR}/doxygen/Doxyfile)
    set(doxy_main_page ${PROJECT_SOURCE_DIR}/doxygen/main.doxy)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doxygen
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${PROJECT_BINARY_DIR}/doxygen/html DESTINATION share/doc)
    install(DIRECTORY ${PROJECT_BINARY_DIR}/doxygen/man DESTINATION share/doc)
    
endif(DOXYGEN_FOUND)

SET(CPACK_GENERATOR "TGZ;TBZ2;DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "BrainTwister")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)
