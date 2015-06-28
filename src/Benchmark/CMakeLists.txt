include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/ArgumentParser/include
)

add_executable(
    Benchmark
    main.cpp
)
    
target_link_libraries(
    Benchmark
    ArgumentParser
    BlasInterface_IntelMKL
)

install(TARGETS Benchmark RUNTIME DESTINATION bin)
