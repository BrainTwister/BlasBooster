if(MKL_FOUND)
  return()
endif(MKL_FOUND)

find_path(MKL_INCLUDE_DIR mkl.h $ENV{MKLROOT}/include)

find_library(MKL_INTEL_LP64_LIBRARY mkl_intel_lp64 $ENV{MKLROOT}/lib/intel64)
find_library(MKL_CORE_LIBRARY mkl_core $ENV{MKLROOT}/lib/intel64)
find_library(MKL_GNU_THREAD_LIBRARY mkl_gnu_thread $ENV{MKLROOT}/lib/intel64)

list(APPEND MKL_LIBRARIES
  ${MKL_INTEL_LP64_LIBRARY}
  ${MKL_CORE_LIBRARY}
  ${MKL_GNU_THREAD_LIBRARY}
  dl pthread m
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MKL DEFAULT_MSG
  MKL_INTEL_LP64_LIBRARY
  MKL_CORE_LIBRARY
  MKL_GNU_THREAD_LIBRARY
)

mark_as_advanced(MKL_LIBRARIES)
