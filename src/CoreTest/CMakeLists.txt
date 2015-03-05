include_directories(
    ${BlasBooster_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
)

add_executable(
    CoreTest
    main.cpp
    AbsoluteValueRangeCheckerTest.cpp
    MatrixConverterTest.cpp
    MultipleMatrixTest.cpp
    SparseMatrixTest.cpp
    StorageTest.cpp
    ThresholdTest.cpp
)
    
target_link_libraries(
    CoreTest
    CoreLib
    ${GTEST_BOTH_LIBRARIES}
)

add_test(
    CoreTest
    ${CMAKE_BINARY_DIR}/bin/CoreTest
    --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/CoreTest.xml
)
