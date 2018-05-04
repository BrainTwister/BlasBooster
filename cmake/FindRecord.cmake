if(RECORD_FOUND)
  return()
endif()

find_path(RECORD_INCLUDE_DIR BrainTwister/Record.h ${RECORD_ROOT}/include)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RECORD DEFAULT_MSG RECORD_INCLUDE_DIR)
