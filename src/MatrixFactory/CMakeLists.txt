include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

add_library(
    MatrixFactory
    STATIC
    MatrixFileImporter.cpp
    MatrixGenerator.cpp
)
