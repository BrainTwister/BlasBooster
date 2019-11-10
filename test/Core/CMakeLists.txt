set(TestName CoreTest)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${RECORD_INCLUDE_DIR}
    ${GTEST_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    ${TestName}
    AbsoluteValueRangeChecker.cpp
    BinaryFunctors.cpp
    BlockedMatrixMultiplication.cpp
    BlockSizeGenerator.cpp
    main.cpp
    MatrixConverter.cpp
    MatrixMultiplication.cpp
    MatrixMultiplicationTyped.cpp
    MatrixNorm.cpp
    MatrixNorm2.cpp
    MultipleMatrix.cpp
    SparseMatrix.cpp
    Storage.cpp
    Threshold.cpp
    Transposition.cpp
    ZeroMatrix.cpp
)
    
target_link_libraries(
    ${TestName}
    ${Boost_LIBRARIES}
    ${CONAN_LIBS}
    ${EXTERNAL_BLAS_LIBRARIES}
    Utilities
    ${GTEST_BOTH_LIBRARIES}
    -pthread
)

add_test(
    NAME ${TestName}
    COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
