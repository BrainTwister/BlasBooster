include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    MatrixFactoryLib
    SHARED
    MatrixFileImporter.cpp
    MatrixGenerator.cpp
)
