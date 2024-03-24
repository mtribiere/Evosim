cmake_minimum_required(VERSION 3.18)

project(EvoSim
    VERSION 0.0.1
    LANGUAGES CXX
)

add_compile_options(-std=gnu++14)
find_package(SDL2 REQUIRED)

add_subdirectory(src/ui)
add_subdirectory(src/entity)
add_subdirectory(src/brain)

add_executable(Evosim src/main.cpp)
target_link_libraries(Evosim 
    entity
    ui
    brain
)