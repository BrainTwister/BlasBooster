include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    Benchmark
    main.cpp
)

target_link_libraries(
    Benchmark
    CoreLib
)

install(TARGETS Benchmark RUNTIME DESTINATION bin)

