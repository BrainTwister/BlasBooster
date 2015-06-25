if (MKL_FOUND)
    return()
endif (MKL_FOUND)

if(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64")

SET(LIB_INSTALL_DIR ${LIB_INSTALL_DIR} "/software/compiler/intel/mkl/*/lib/em64t")
SET(LIB_INSTALL_DIR ${LIB_INSTALL_DIR} "/software/compiler/intel/mkl/lib/intel64")

find_library(MKL_LIBRARIES
  mkl_core
  PATHS
  $ENV{MKLLIB}
  ${LIB_INSTALL_DIR}
)

find_library(MKL_GUIDE
  guide
  PATHS
  $ENV{MKLLIB}
  ${LIB_INSTALL_DIR}
)

if(MKL_LIBRARIES)
  set(MKL_LIBRARIES ${MKL_LIBRARIES} mkl_intel_lp64 mkl_gnu_thread mkl_blas95_lp64 pthread)
endif()

if(MKL_GUIDE)
  set(MKL_LIBRARIES ${MKL_LIBRARIES} ${MKL_GUIDE})
endif()

else(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64")

SET(LIB_INSTALL_DIR ${LIB_INSTALL_DIR} "/software/intel/mkl/*/lib/ia32")
SET(LIB_INSTALL_DIR ${LIB_INSTALL_DIR} "/software/intel/mkl/lib/ia32")

find_library(MKL_LIBRARIES
  mkl_core
  PATHS
  $ENV{MKLLIB}
  ${LIB_INSTALL_DIR}
)

find_library(MKL_GUIDE
  guide
  PATHS
  $ENV{MKLLIB}
  ${LIB_INSTALL_DIR}
)

if(MKL_LIBRARIES)
  set(MKL_LIBRARIES ${MKL_LIBRARIES} mkl_intel mkl_gnu_thread mkl_blas95 pthread)
endif()

if(MKL_GUIDE)
  set(MKL_LIBRARIES ${MKL_LIBRARIES} ${MKL_GUIDE})
endif()

endif(${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MKL DEFAULT_MSG MKL_LIBRARIES)

mark_as_advanced(MKL_LIBRARIES)

find_path( MKL_INCLUDE_DIR
    mkl.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
    /software/compiler/intel/mkl/include
    /software/intel/mkl/include
)
