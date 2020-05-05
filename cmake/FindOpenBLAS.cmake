if (OPENBLAS_FOUND)
  return()
endif (OPENBLAS_FOUND)

find_library(OPENBLAS_LIBRARY
  NAMES libopenblas.a
  PATHS ${OPENBLAS_ROOT}/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenBLAS DEFAULT_MSG OPENBLAS_LIBRARY)
