include_directories(
    ${Boost_INCLUDE_DIRS}
    ${RECORD_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    MatrixFactory
    STATIC
    MatrixFileImporter.cpp
    MatrixGenerator.cpp
)
