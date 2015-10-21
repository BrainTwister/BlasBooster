set(TestName DesignTest)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

add_executable(
    ${TestName}
    BoostPropertyTree.cpp
    DynamicType.cpp
    main.cpp
    unpackTwoVariadicTemplates.cpp
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
