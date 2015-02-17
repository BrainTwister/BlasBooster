include_directories(
    ${BlasBooster_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
)

add_executable(
    CoreGTest
    main.cpp
    AbsoluteValueRangeCheckerTest.cpp
    MatrixConverterTest.cpp
    MultipleMatrixTest.cpp
    SparseMatrixTest.cpp
    StorageTest.cpp
    ThresholdTest.cpp
)
    
target_link_libraries(
    CoreGTest
    CoreLib
    ${GTEST_BOTH_LIBRARIES}
)

add_test(
    CoreGTest
    ${CMAKE_BINARY_DIR}/bin/CoreGTest
    --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/CoreGTest.xml
)
