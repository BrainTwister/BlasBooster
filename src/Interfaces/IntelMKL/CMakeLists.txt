include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${MKL_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

add_library(
    BlasInterface_IntelMKL
    SHARED
    BlasInterface_IntelMKL.cpp
)

target_link_libraries(
    BlasInterface_IntelMKL
    ${MKL_LIBRARIES}
)

install(TARGETS BlasInterface_IntelMKL LIBRARY DESTINATION lib)
