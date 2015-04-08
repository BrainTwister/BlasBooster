set(TestName CoreTest)

include_directories(
    ${BlasBooster_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
)

file(GLOB SOURCES *.cpp)

add_executable(
    ${TestName}
    ${SOURCES}
)
    
target_link_libraries(
    ${TestName}
    CoreLib
    ${GTEST_BOTH_LIBRARIES}
)

add_test(
    ${TestName}
    ${CMAKE_BINARY_DIR}/bin/${TestName}
    --gtest_output=xml:${CMAKE_BINARY_DIR}/Testing/${TestName}.xml
)
