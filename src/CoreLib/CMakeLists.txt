include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    CoreLib
    SHARED
    BlockSizeGenerator.cpp
    GenerateTypeMatrix.cpp
)

#target_link_libraries(
#    CoreLib
#    IntelMKL
#)
