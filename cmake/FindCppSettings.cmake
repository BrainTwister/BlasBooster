if(CPPSETTINGS_FOUND)
  return()
endif()

find_path(CPPSETTINGS_INCLUDE_DIR BrainTwister/Settings.h ${CPPSETTINGS_ROOT}/include)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CppSettings DEFAULT_MSG CPPSETTINGS_INCLUDE_DIR)
