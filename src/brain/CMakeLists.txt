find_package (Eigen3 REQUIRED)

add_library(brain
    brain.cpp
)
target_include_directories(brain PUBLIC
    includes
    MiniDNN/include
)
target_link_libraries(brain
    Eigen3::Eigen
)