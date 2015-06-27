include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
)

add_executable(
    ArgumentParserTest
    main.cpp
    ArgumentParser.cpp
    Design.cpp
)
    
target_link_libraries(
    ArgumentParserTest
    ArgumentParser
    ${GTEST_BOTH_LIBRARIES}
)

add_test(
    ArgumentParserTest
    ${CMAKE_BINARY_DIR}/bin/ArgumentParserTest
    --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/ArgumentParserTest.xml
)
