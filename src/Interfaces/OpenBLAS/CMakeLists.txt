include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    BlasInterface_OpenBLAS
    SHARED
    BlasInterface_OpenBLAS.cpp
)

target_link_libraries(
    BlasInterface_OpenBLAS
    ${OPENBLAS_LIBRARIES}
)

install(TARGETS BlasInterface_OpenBLAS LIBRARY DESTINATION lib)
