include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/ArgumentParser/include
    ${Boost_INCLUDE_DIRS}
)

add_executable(
    Coeff2Dens
    Coeff2Dens.cpp
)
    
target_link_libraries(
    Coeff2Dens
    ArgumentParser
    ${EXTERNAL_BLAS_LIBRARIES}
    ${Boost_LIBRARIES}
)

install(TARGETS Coeff2Dens RUNTIME DESTINATION bin)

add_executable(
    ShowPattern
    ShowPattern.cpp
)
    
target_link_libraries(
    ShowPattern
    ArgumentParser
    MatrixFactory
    ${Boost_LIBRARIES}
)

install(TARGETS ShowPattern RUNTIME DESTINATION bin)

