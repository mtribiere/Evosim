add_library(entity
    env.cpp
    entity.cpp
    pipe.cpp
    bird.cpp
)
target_include_directories(entity PUBLIC
    includes
)
target_link_libraries(entity PUBLIC
    ui
    brain
)