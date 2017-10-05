include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CPPSETTINGS_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    MatrixFactory
    STATIC
    MatrixFileImporter.cpp
    MatrixGenerator.cpp
)
