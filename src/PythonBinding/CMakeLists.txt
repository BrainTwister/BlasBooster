include_directories(
    /usr/include/python3.5m
    ${PROJECT_SOURCE_DIR}/include
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
