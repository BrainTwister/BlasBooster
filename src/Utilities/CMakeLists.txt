include_directories(
    ${CONAN_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    Utilities
    SHARED
    tracker.cpp
)

target_link_libraries(
    Utilities
    ${CONAN_LIBS}
)

install(TARGETS Utilities LIBRARY DESTINATION lib)
