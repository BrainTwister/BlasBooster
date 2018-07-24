set(TestName DesignTest)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

add_executable(
    ${TestName}
    DynamicType.cpp
    main.cpp
    range-v3.cpp
    unpackTwoVariadicTemplates.cpp
)
    
target_link_libraries(
    ${TestName}
    ${CONAN_LIBS}
    ${GTEST_BOTH_LIBRARIES}
    -pthread
)

add_test(
    NAME ${TestName}
    COMMAND ${TestName} --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
