set(TestName UtilitiesTest)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

add_executable(
    ${TestName}
    main.cpp
    TypeList.cpp
)
    
target_link_libraries(
    ${TestName}
    ${Boost_LIBRARIES}
    ${CONAN_LIBS}
    ${GTEST_BOTH_LIBRARIES}
    -pthread
)

add_test(
    NAME ${TestName}
    COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
