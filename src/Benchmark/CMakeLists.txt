include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/ArgumentParser/include
    ${PROJECT_SOURCE_DIR}/BenchmarkManager/include
    ${Boost_INCLUDE_DIRS}
)

add_executable(
    Benchmark
    main.cpp
)
    
target_link_libraries(
    Benchmark
    ArgumentParser
    BlasInterface_IntelMKL
    BlasInterface_OpenBLAS
    ${Boost_LIBRARIES}
)

install(TARGETS Benchmark RUNTIME DESTINATION bin)
