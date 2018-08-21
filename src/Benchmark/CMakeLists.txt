include_directories(
    ${CONAN_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    benchmark
    ActionProvider.cpp
    benchmark.cpp
    MatrixProvider.cpp
    time.cpp
)
    
target_link_libraries(
    benchmark
    ${CONAN_LIBS}
    ${EXTERNAL_BLAS_LIBRARIES}
    Utilities
)

add_executable(
    show_pattern
    show_pattern.cpp
)
    
target_link_libraries(
    show_pattern
    ${CONAN_LIBS}
    ${EXTERNAL_BLAS_LIBRARIES}
    Utilities
)

install(TARGETS benchmark show_pattern RUNTIME DESTINATION bin)

add_executable(
    generate_matrix
    generate_matrix.cpp
)
    
target_link_libraries(
    generate_matrix
    ${CONAN_LIBS}
    ${EXTERNAL_BLAS_LIBRARIES}
    Utilities
)

install(TARGETS benchmark generate_matrix RUNTIME DESTINATION bin)
