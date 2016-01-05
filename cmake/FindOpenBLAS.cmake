if (OPENBLAS_FOUND)
  return()
endif (OPENBLAS_FOUND)

message("OpenBLAS = ${OPENBLAS_ROOT}")

find_library(OPENBLAS_LIBRARY
  NAMES libopenblas.a
  PATHS ${OPENBLAS_ROOT}/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OPENBLAS DEFAULT_MSG OPENBLAS_LIBRARY)
