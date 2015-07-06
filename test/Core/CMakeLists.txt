set(TestName CoreTest)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
)

add_executable(
    ${TestName}
    AbsoluteValueRangeCheckerTest.cpp
    main.cpp
    MatrixConverterTest.cpp
    MatrixMultiplicationTest.cpp
    MultipleMatrixTest.cpp
    SparseMatrixTest.cpp
    StorageTest.cpp
    ThresholdTest.cpp
)
    
target_link_libraries(
    ${TestName}
    ${GTEST_BOTH_LIBRARIES}
    -pthread
)

add_test(
    NAME ${TestName}
    COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
