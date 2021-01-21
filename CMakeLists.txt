cmake_minimum_required(VERSION 3.0)
project(BlasBooster VERSION 0.3 LANGUAGES CXX)

message(STATUS "${PROJECT_NAME} version ${PROJECT_VERSION}")

# Set release as default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "CMake build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -DBLASBOOSTER_USE_TRACKER")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -mfma")

# https://github.com/pybind/pybind11/issues/1818
if(${CMAKE_CXX_COMPILER} MATCHES "clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsized-deallocation")
endif()

# C++ ISO standard
set(CPP_ISO_STANDARD "c++17" CACHE STRING "C++ ISO standard")
message(STATUS "Use ${CPP_ISO_STANDARD} ISO standard")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CPP_ISO_STANDARD}")

# CMake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_program(CONAN conan)
if(CONAN)
    # Download conan-cmake
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
       message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
       file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.15/conan.cmake"
                     "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()
    
    # Conan setup
    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_cmake_run(CONANFILE conanfile.txt
                    BASIC_SETUP CMAKE_TARGETS NO_OUTPUT_DIRS
                    SETTINGS compiler.libcxx=libstdc++11
                    BUILD_TYPE "None"
                    BUILD missing)
    
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    set(CONAN_SYSTEM_INCLUDES "On")
    conan_basic_setup(NO_OUTPUT_DIRS)
endif()

# Use OpenMP
#if(${CMAKE_CXX_COMPILER} MATCHES "clang")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp=libomp")
#else()
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
#endif()

if(${CMAKE_CXX_COMPILER} MATCHES "icpc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__GXX_EXPERIMENTAL_CXX0X__ -DNO_INITIALIZER_LIST_SUPPORTED")
endif()

if(${CMAKE_COMPILER_IS_GNUCXX})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=10000 -msse2 -ftrack-macro-expansion=0")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -funroll-loops -ffast-math -mfpmath=sse -march=core2 -mtune=core2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops --param max-unroll-times=100 -ffast-math -mfpmath=sse -march=core2 -mtune=core2")
endif()

# Set RPATH relative to executable
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")

set(CMAKE_VERBOSE_MAKEFILE false)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Get Git revision
if(EXISTS ${PROJECT_SOURCE_DIR}/.git)
    find_package(Git)
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            OUTPUT_VARIABLE "GIT_REVISION"
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE)
        message(STATUS "Git revision: ${GIT_REVISION}")
    else()
        set(GIT_REVISION 0)
    endif()
endif()

# Generate version and revision string
configure_file (
    "${PROJECT_SOURCE_DIR}/include/BlasBooster/Utilities/Version.h.in"
    "${PROJECT_SOURCE_DIR}/include/BlasBooster/Utilities/Version.h"
)

# Boost template libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost)
if(Boost_FOUND)
    add_definitions(-DUSE_BOOST -DHAVE_SHARED_POINTER -DBOOST_DATE_TIME_POSIX_TIME_STD_CONFIG -DBOOST_SYSTEM_NO_DEPRECATED)
endif(Boost_FOUND)

# List for external BLAS interfaces
set(EXTERNAL_BLAS_LIBRARIES "")

find_package(Record REQUIRED)

# Intel math kernel library (MKL)
find_package(MKL)
if(MKL_FOUND)
    add_definitions(-DWITH_INTELMKL)
    add_subdirectory(src/Interfaces/IntelMKL)
    list(APPEND EXTERNAL_BLAS_LIBRARIES BlasInterface_IntelMKL)
endif(MKL_FOUND)

# GotoBLAS/OpenBLAS 
find_package(OpenBLAS)
if(OPENBLAS_FOUND)
    add_definitions(-DWITH_OPENBLAS)
    add_subdirectory(src/Interfaces/OpenBLAS)
    list(APPEND EXTERNAL_BLAS_LIBRARIES BlasInterface_OpenBLAS)
endif(OPENBLAS_FOUND)

# Eigen 
find_package(Eigen3)
if(EIGEN3_FOUND)
    add_definitions(-DWITH_EIGEN)
endif(EIGEN3_FOUND)

#find_package(blaze REQUIRED)

add_subdirectory(src/Benchmark)
add_subdirectory(src/MatrixFactory)
add_subdirectory(src/Utilities)

# PyBind
set(PYBIND11_PYTHON_VERSION 3)
find_package(pybind11 QUIET)
if(pybind11_FOUND)
    add_subdirectory(src/PythonBinding)
else()
    message(STATUS "Could NOT find pybind11")
endif()

# Google C++ unit test framework
find_package(GTest)
if(GTEST_FOUND)
    ENABLE_TESTING()
    add_subdirectory(test)
endif(GTEST_FOUND)

# Doxygen API documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)

    set(doxyfile_in ${PROJECT_SOURCE_DIR}/docs/Doxyfile.in)
    set(doxyfile ${PROJECT_BINARY_DIR}/docs/Doxyfile)
    set(doxy_main_page ${PROJECT_SOURCE_DIR}/docs/main.doxy)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${PROJECT_BINARY_DIR}/docs/html DESTINATION share/doc)
    install(DIRECTORY ${PROJECT_BINARY_DIR}/docs/man DESTINATION share/doc)
    
endif(DOXYGEN_FOUND)

SET(CPACK_GENERATOR "TGZ;TBZ2;DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "BrainTwister")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)
