if (OPENBLAS_FOUND)
    return()
endif (OPENBLAS_FOUND)

find_library( OPENBLAS_LIBRARY
    libopenblas.so
    PATHS
    $ENV{OPENBLAS_ROOT}/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OPENBLAS DEFAULT_MSG OPENBLAS_LIBRARY)
