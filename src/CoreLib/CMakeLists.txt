include_directories(
    ..
    ../BoostLib
    ../IntelMKL
    ../PreprocessorLib
    ../UtilitiesLib
)

add_library(
    CoreLib
    SHARED
    BlockSizeGenerator.cpp
    GenerateTypeMatrix.cpp
)

target_link_libraries(
    CoreLib
    IntelMKL
)
