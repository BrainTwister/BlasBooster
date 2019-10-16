include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

include_directories(SYSTEM
    ${PYTHON_INCLUDE_DIRS}
)

add_library(
    BlasBooster
    SHARED    
    matrix.cpp
)
    
target_link_libraries(
    BlasBooster
    ${CONAN_LIBS}
)

pybind11_add_module(blasbooster MODULE matrix.cpp)
