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
    ${GTEST_BOTH_LIBRARIES}
    -pthread
    ${Boost_LIBRARIES}
    BlasInterface_IntelMKL
    BlasInterface_OpenBLAS
)

add_test(
    NAME ${TestName}
    COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
