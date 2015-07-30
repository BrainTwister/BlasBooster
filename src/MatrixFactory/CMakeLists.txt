include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    MatrixFactory
    SHARED
    MatrixFileImporter.cpp
    MatrixGenerator.cpp
)
