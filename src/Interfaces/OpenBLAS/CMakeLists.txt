include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

add_library(
    BlasInterface_OpenBLAS
    SHARED
    BlasInterface_OpenBLAS.cpp
)

target_link_libraries(
    BlasInterface_OpenBLAS
    ${CONAN_LIBS}
    ${OPENBLAS_LIBRARY}
)

install(TARGETS BlasInterface_OpenBLAS LIBRARY DESTINATION lib)
