if(MTL4_FOUND)
  return()
endif(MTL4_FOUND)

find_path(MTL4_INCLUDE_DIR boost/numeric/mtl/mtl.hpp $ENV{MTL4_ROOT}/usr/include)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MTL4 DEFAULT_MSG MTL4_INCLUDE_DIR)
