include_directories(
    ${CONAN_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    benchmark
    benchmark.cpp
)
    
target_link_libraries(
    benchmark
    ${CONAN_LIBS}
    ${EXTERNAL_BLAS_LIBRARIES}
)

add_executable(
    show_pattern
    show_pattern.cpp
)
    
target_link_libraries(
    show_pattern
    ${CONAN_LIBS}
    ${EXTERNAL_BLAS_LIBRARIES}
)

install(TARGETS benchmark show_pattern RUNTIME DESTINATION bin)
