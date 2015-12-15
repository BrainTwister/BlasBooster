set(TestName CoreTest)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

add_executable(
    ${TestName}
    AbsoluteValueRangeCheckerTest.cpp
    BinaryFunctors.cpp
    main.cpp
    MatrixConverterTest.cpp
    MatrixMultiplicationTest.cpp
    MatrixNorm.cpp
    MatrixNorm2.cpp
    MultipleMatrixTest.cpp
    SparseMatrixTest.cpp
    StorageTest.cpp
    ThresholdTest.cpp
    Transposition.cpp
)
    
target_link_libraries(
    ${TestName}
    ${Boost_LIBRARIES}
    ${EXTERNAL_BLAS_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
    -pthread
)

add_test(
    NAME ${TestName}
    COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
