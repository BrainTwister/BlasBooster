include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    ArgumentParser
    ArgumentParser.cpp
)
    
target_link_libraries(
    ArgumentParser
)
